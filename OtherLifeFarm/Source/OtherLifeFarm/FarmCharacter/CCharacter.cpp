#include "CCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"	
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Tools/CRake.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/CInventory.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Characters/Mannequins/Meshes/SKM_Manny"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClass(TEXT("/Game/Characters/Mannequins/Animations/ABP_Manny"));
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
		}
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

	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &ACCharacter::MouseLeft);
	PlayerInputComponent->BindAction("OpenSkillWindow", IE_Pressed, this, &ACCharacter::OpenWindowSkill);
	PlayerInputComponent->BindAction("OpenInventory", IE_Pressed, this, &ACCharacter::OpenInventory);
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
			Rake->bPlayerAnimation = true;
		}
		else
		{
			SkillWindowWidget->AddToViewport();
			Rake->bPlayerAnimation = false;
		}
	}
}

void ACCharacter::OpenInventory()
{
	if (CInventoryWidget)
	{
		if (CInventoryWidget->GetInventoryOpen() == false)
		{
			CInventoryWidget->SetInventoryOpen(true);
			CInventoryWidget->ToggleInventory();

		}

		if (CInventoryWidget->GetInventoryOpen()== true)
		{
			CInventoryWidget->SetInventoryOpen(false);
			CInventoryWidget->ToggleInventory();
		}
	}
}

void ACCharacter::MouseLeft()
{
	if (Rake && Rake->bPlayerAnimation)
	{
		Rake->Plowing();
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

