#include "Widget/CGameQuit.h"
#include "PlayerController/CPlayerController.h"

void UCGameQuit::NativeConstruct()
{

	Super::NativeConstruct();
	
	ACPlayerController* PC = Cast<ACPlayerController>(GetOwningPlayer());

	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct Runned: %p"), this);


	if (PC)
	{
		PC->OnCancelPressed.AddDynamic(this, &UCGameQuit::HandleCancel);
		UE_LOG(LogTemp, Warning, TEXT("Delegate Binding Success  : %p"), this);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController finding failed"));
	}


}

void UCGameQuit::NativeDestruct()
{
	ACPlayerController* PC = Cast<ACPlayerController>(GetOwningPlayer());

	if (PC)
	{
		PC->OnCancelPressed.RemoveDynamic(this, &UCGameQuit::HandleCancel);
	}


}

void UCGameQuit::HandleCancel()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleCancel"));

	ACPlayerController* PC = Cast<ACPlayerController>(GetOwningPlayer());

	if (PC && !PC->UIStack.Contains(this))
	{
		PC->UIStack.Add(this);
	}
}
