#include "PlayerController/CPlayerController.h"
#include "GameInstance/CGameInstance.h"
#include "Grain/CRice.h"
#include "FarmCharacter/CCharacter.h"


void ACPlayerController::BeginPlay()
{
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseLeft", IE_Pressed, this, &ACPlayerController::OnLeftClick);
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
