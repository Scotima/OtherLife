#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CDialogueWidget.generated.h"

UCLASS()
class OTHERLIFEFARM_API UCDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetDialogue(const FString& Text);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DialogueText;
	
};
