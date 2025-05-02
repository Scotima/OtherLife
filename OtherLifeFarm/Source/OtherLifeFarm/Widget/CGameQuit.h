
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGameQuit.generated.h"


UCLASS()
class OTHERLIFEFARM_API UCGameQuit : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

public:
	UFUNCTION()
	void HandleCancel();


	
};
