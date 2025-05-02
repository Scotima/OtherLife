#include "CCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"	
#include "GameFramework/PlayerController.h"
#include "PlayerController/CPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Tools/CRake.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CInventory.h"
#include "Inventory/CItemWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CNpcone.h"
#include "GameInstance/CGameInstance.h"
#include "Grain/CRice.h"
#include "DialogueWidget/CDialogueWidget.h"
#include "CFlick.h"
#include "AIController.h"
#include "BrainComponent.h"



ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/FarmGame/BPCharacter/CharacterAsset/Boy/Boy"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClass(TEXT("/Game/FarmGame/BPCharacter/ABP_BOY"));
	if (AnimInstanceClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
	}

	ConstructorHelpers::FClassFinder<ACRake> ToolClass(TEXT("/Game/FarmGame/Tools/BP_Rake"));

	if (ToolClass.Succeeded())
	{
		RakeClass = ToolClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> CursorWidgetAsset(TEXT("/Game/FarmGame/UI/WG_MouseCursor"));

	if (CursorWidgetAsset.Succeeded())
	{
		CursorWidgetClass = CursorWidgetAsset.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> SkillWindowAsset(TEXT("/Game/FarmGame/UI/WG_OpenSkillWindow"));

	if (SkillWindowAsset.Succeeded())
	{
		SkillWindowClass = SkillWindowAsset.Class;
	}

	ConstructorHelpers::FClassFinder<UCInventory> InventoryWidget(TEXT("/Game/FarmGame/UI/WG_INVENTORY"));

	if (InventoryWidget.Succeeded())
	{
		CInventoryClass = InventoryWidget.Class;
	}
	
	ConstructorHelpers::FClassFinder<UCItemWidget> ItemWidgetAsset(TEXT("/Game/FarmGame/UI/BP_ItemWidget"));

	if (ItemWidgetAsset.Succeeded())
	{
		InventoryWidgetClass = ItemWidgetAsset.Class;
	}

	


	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 100));
	SpringArmComp->SetRelativeRotation(FRotator(-88, 0, 0));
	SpringArmComp->TargetArmLength = 800.f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0, 60, 700);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	playanim = false;

	ItemIndex = 0;

	


}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetCustomMouseCursor();

	if (RakeClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		Rake = GetWorld()->SpawnActor<ACRake>(RakeClass, SpawnParams);

	}
	if (SkillWindowClass)
	{
		SkillWindowWidget = CreateWidget<UUserWidget>(GetWorld(), SkillWindowClass);
		
	}

	if (CInventoryClass)
	{
		CInventoryWidget = CreateWidget<UCInventory>(GetWorld(), CInventoryClass);

		if (CInventoryWidget)
		{
			CInventoryWidget->AddToViewport();
			CInventoryWidget->SetVisibility(ESlateVisibility::Hidden);

			CInventoryWidget->LoadInventory();
			CInventoryWidget->LoadSaveInventory();
		}
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CInventoryClass is none!"));
	}

	if (InventoryWidgetClass)
	{
		ManageInventoryWidget = CreateWidget<UCItemWidget>(GetWorld(), InventoryWidgetClass);
		if (ManageInventoryWidget)
		{
			ManageInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		}

	}

	

	UCGameInstance* mygameinstance = Cast<UCGameInstance>(GetGameInstance());
	if (mygameinstance)
	{
		coin = mygameinstance->coin;
	}

	
	
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	


}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACCharacter::MoveRight);

	
	PlayerInputComponent->BindAction("OpenSkillWindow", IE_Pressed, this, &ACCharacter::OpenWindowSkill);
	PlayerInputComponent->BindAction("OpenInventory", IE_Pressed, this, &ACCharacter::OpenInventory);
	
	PlayerInputComponent->BindAction("Line", IE_Pressed, this, &ACCharacter::DoLineTrace);
}

void ACCharacter::MoveForward(float value)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(Direction, value);
}

void ACCharacter::MoveRight(float value)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetRightVector().GetSafeNormal2D();

	AddMovementInput(Direction, value);
}

void ACCharacter::OpenWindowSkill()
{
	if (SkillWindowWidget)
	{
		IsVisible = SkillWindowWidget->IsInViewport();

		if (IsVisible)
		{
			SkillWindowWidget->RemoveFromViewport();
			
		}
		else
		{
			SkillWindowWidget->AddToViewport();
			
		}
	}
}

void ACCharacter::OpenInventory()
{
	if (CInventoryWidget)
	{
		CInventoryWidget->ToggleInventory();
	}
}

void ACCharacter::PickupItem(FItemStruct NewItem)
{
	if (ManageInventoryWidget)
	{
		if (CInventoryWidget)
		{

			UCGameInstance* mygameinstance = Cast<UCGameInstance>(GetGameInstance());
			if(mygameinstance)
			{ 
				for (int i = 1; i < 9; i++)
				{
					int index = i - 1;
					if (index < mygameinstance->Data.Num())
					{
						if (mygameinstance->Data[index].ItemName.Len() == 0)
						{
							mygameinstance ->Data[index] = NewItem;
							CInventoryWidget->SetInven(index);
							mygameinstance->SaveInventoryData(mygameinstance->Data);
							
							return;

						}
						if (NewItem.ItemName == mygameinstance->Data[index].ItemName)
						{
							mygameinstance->Data[index].ItemCount += NewItem.ItemCount;
							CInventoryWidget->SetInven(index);
							mygameinstance->SaveInventoryData(mygameinstance->Data);
							
							return;
						}
					}
				}

				mygameinstance->AddData(NewItem);
				CInventoryWidget->SetInven(ItemIndex);

				ItemIndex++;
			}


		}



	}
}



void ACCharacter::SetCustomMouseCursor()
{
	APlayerController* PlayerController = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is nullptr"));
		return;
	}

	if (CursorWidgetClass)
	{
		UUserWidget* CursorWidget = CreateWidget<UUserWidget>(GetWorld(), CursorWidgetClass);

		if (CursorWidget)
		{
			PlayerController->SetMouseCursorWidget(EMouseCursor::Default, CursorWidget);
			PlayerController->bShowMouseCursor = true;

			UE_LOG(LogTemp, Log, TEXT("Custom mouse cursor set."));
		}
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Custom Cursor WidgetAsset is null"));
	}
}

void ACCharacter::DoLineTrace()
{
	FVector Start = GetActorLocation();
	FVector Forward = GetActorForwardVector();

	FVector End = Start + (Forward * 2000.0f);

	TArray<FHitResult> hitresult;
	FCollisionQueryParams params;

	params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceMultiByChannel(hitresult, Start, End, ECC_Visibility, params);



	if (bHit)
	{
		if (CurrentWidget && CurrentWidget->IsInViewport())
		{
			return;
		}

		for (const FHitResult& Hit : hitresult)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->Implements<UCCharacterInterFace>())
			{
				
				
				if (ACFlick* npc2 = Cast<ACFlick>(HitActor))
				{
					ACPlayerController* PC = Cast<ACPlayerController>(GetController());
					if (PC)
					{
						npc2->StartTalking();

						
						if (AAIController* NPCController = Cast<AAIController>(npc2->GetController()))
						{
							NPCController->StopMovement();

							if (NPCController->BrainComponent)
							{
								NPCController->BrainComponent->StopLogic("Talking");
							}
							NPCController->SetFocus(this);

							npc2->bUseControllerRotationYaw = true;
							npc2->GetCharacterMovement()->bOrientRotationToMovement = false;
						}

						PC->SetViewTargetWithBlend(HitActor, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
						this->GetCharacterMovement()->DisableMovement();

						if (DialogueWidgetInstance == nullptr)
						{
							DialogueWidgetInstance = CreateWidget<UCDialogueWidget>(GetWorld(), DialogueWidgetClass);
						}

						if (DialogueWidgetInstance)
						{
							DialogueWidgetInstance->SetDialogue(TEXT("여기가 바로 꿈꾸던 농장이군요!"));

							DialogueWidgetInstance->AddToViewport();
							DialogueWidgetInstance->SetPlayer(this);

							

							FInputModeGameAndUI InputMode;
							InputMode.SetWidgetToFocus(DialogueWidgetInstance->TakeWidget());
							InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
							InputMode.SetHideCursorDuringCapture(false);
							PC->SetInputMode(InputMode);
							PC->bShowMouseCursor = true;
							
							if (!PC->UIStack.Contains(DialogueWidgetInstance))
							{
								PC->UIStack.Add(DialogueWidgetInstance);
							}


							CurrentWidget = DialogueWidgetInstance;
							InteractedNPC = npc2;

							
						}
					}
					


				}


				UUserWidget* widget = ICCharacterInterFace::Execute_ShowWidget(HitActor);

			


				if (widget && !widget->IsInViewport())
				{
					widget->AddToViewport();
					CurrentWidget = widget;
				}

					
				if (ACNpcone* NPC = Cast<ACNpcone>(HitActor))
				{
					APlayerController* PC = Cast<APlayerController>(GetController());

					if (PC)
					{
						NPC->SetTalking(true);
						PC->SetViewTargetWithBlend(HitActor, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
						LastInteractedNPC = NPC;
						this->GetCharacterMovement()->SetMovementMode((MOVE_None));
							
					}
				}
					
				
				break;
			}
		}
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 2.0f, 0, 2.0f);

}

void ACCharacter::SetCoin(int64 a)
{
	UCGameInstance* mygameinstance = Cast<UCGameInstance>(GetGameInstance());

	if (mygameinstance)
	{
		mygameinstance->coin += a;

		coin = mygameinstance->coin;
	}
}

void ACCharacter::CameraOriginalPos()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (CurrentWidget)
	{
		CurrentWidget = nullptr;
	}
	
	if (LastInteractedNPC)
	{

		if (PC)
		{
			PC->SetViewTargetWithBlend(this, 0.5f); // 카메라 원위치로 돌아오게 하는 기능
			LastInteractedNPC->SetTalking(false);

			LastInteractedNPC = nullptr;
			this->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}
	
}

void ACCharacter::EndDialogue()
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	

	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	if(DialogueWidgetInstance && DialogueWidgetInstance->IsInViewport())
	{
		DialogueWidgetInstance->RemoveFromParent();
	}

	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	if (InteractedNPC)
	{
		InteractedNPC->StopTalking();

		if (AAIController* NPCController = Cast<AAIController>(InteractedNPC->GetController()))
		{
			NPCController->ClearFocus(EAIFocusPriority::Default);

			InteractedNPC->bUseControllerRotationYaw = false;
			InteractedNPC->GetCharacterMovement()->bOrientRotationToMovement = true;

			if (NPCController->BrainComponent)
			{
				NPCController->BrainComponent->RestartLogic();
			}
		}
	}

	InteractedNPC = nullptr;

	//카메라 원래대로 복귀
	if (PC)
	{
		PC->SetViewTargetWithBlend(this, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);

	}

}




