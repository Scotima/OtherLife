#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CDialogueWidget.generated.h"

class ACCharacter;

UCLASS()
class OTHERLIFEFARM_API UCDialogueWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION()
	void CancelDialogueWidgetWindow();

	void SetPlayer(ACCharacter* a) { player = a; }
public:
	UFUNCTION(BlueprintCallable)
	void SetDialogue(const FString& Text);



protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DialogueText;


private:
	ACCharacter* player;
	
};
