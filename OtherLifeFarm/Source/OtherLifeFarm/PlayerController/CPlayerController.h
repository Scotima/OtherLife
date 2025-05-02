#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancelPressed);

UCLASS()
class OTHERLIFEFARM_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void HandleCancelPressed();

	void GameQuitMenu();



public:
	TArray<UUserWidget*> UIStack;

public:
	UPROPERTY(BlueprintAssignable)
	FOnCancelPressed OnCancelPressed;

	UPROPERTY(EditAnywhere, Category = "QuitUI")
	TSubclassOf<UUserWidget> GameQuitWidgetClass;

private:
	void OnLeftClick();

private:
	class UCGameQuit* NewUI;
	
};
