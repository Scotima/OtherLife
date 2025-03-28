
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CCharacterInterFace.generated.h"

UINTERFACE(MinimalAPI)
class UCCharacterInterFace : public UInterface
{
	GENERATED_BODY()
};

class OTHERLIFEFARM_API ICCharacterInterFace
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	UUserWidget* ShowWidget();
};
