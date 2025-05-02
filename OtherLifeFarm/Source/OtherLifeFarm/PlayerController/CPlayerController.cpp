#include "PlayerController/CPlayerController.h"
#include "GameInstance/CGameInstance.h"
#include "Grain/CRice.h"
#include "FarmCharacter/CCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Widget/CGameQuit.h"


void ACPlayerController::BeginPlay()
{
	if (GameQuitWidgetClass)
	{
		NewUI = CreateWidget<UCGameQuit>(this, GameQuitWidgetClass);
	}
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseLeft", IE_Pressed, this, &ACPlayerController::OnLeftClick);
	InputComponent->BindAction("Cancel", IE_Pressed, this, &ACPlayerController::HandleCancelPressed);
}

void ACPlayerController::HandleCancelPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancel key input"));

	if (UIStack.Num() > 0)
	{
		UIStack.Last()->RemoveFromParent();
		UIStack.Pop();	

		return;
	}

	GameQuitMenu();

	UE_LOG(LogTemp, Warning, TEXT("Delegate broadcast Start"));

	OnCancelPressed.Broadcast();
	
	UE_LOG(LogTemp, Warning, TEXT("Delegate broadcast compelete"));
	
	
}

void ACPlayerController::GameQuitMenu()
{
	if (GameQuitWidgetClass)
	{
		
		//UIStack.Add(NewUI);
		NewUI->AddToViewport();
	}
}



void ACPlayerController::OnLeftClick()
{
	UE_LOG(LogTemp, Warning, TEXT("SetDestoryActor"));

	UCGameInstance* GI = Cast<UCGameInstance>(GetGameInstance());
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (GI)
	{
		bool destory = GI->bIsDestroyMode;

		if (destory)
		{
			FHitResult Hit;
			if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Hit))
			{
				if (ACRice* HitRice = Cast<ACRice>(Hit.GetActor()))
				{
					HitRice->RemoveMe();
					
					ACCharacter* character = Cast<ACCharacter>(GetPawn());
					character->playanim = false;

				}
			}
		}
	}
}
