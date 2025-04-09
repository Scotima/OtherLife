
#include "GameMode/MyGameModeBase.h"
#include "PlayerController/CPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerClass(TEXT("/Game/FarmGame/BPCharacter/BP_Character"));
	if (PlayerClass.Succeeded())
	{
		DefaultPawnClass = PlayerClass.Class;

		PlayerControllerClass = ACPlayerController::StaticClass();
	}
}