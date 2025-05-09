
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inventory/FItemStruct.h"
#include "InterFace/CCharacterInterFace.h"
#include "CCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACRake;
class UUserWidget;
class UCManageInventory;
class ACGhostRice;
class ACNpcone;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class OTHERLIFEFARM_API ACCharacter : public ACharacter, public ICCharacterInterFace
{
	GENERATED_BODY()

public:
	ACCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float value);

	void MoveRight(float value);

	void SetCustomMouseCursor();

	void DoLineTrace();




public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenWindowSkill();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenInventory();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PickupItem(FItemStruct NewItem);

	UFUNCTION(BlueprintCallable, Category = "coin")
	int64 GetCoin() { return coin; } // todo 상점 기능을 구현해보자

	UFUNCTION(BlueprintCallable, Category = "Coin")
	void SetCoin(int64 a);
	
	UFUNCTION(BlueprintCallable, Category = "Coin")
	void CameraOriginalPos();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void EndDialogue();


	
	void Setshouldmove(bool a) { shouldmove = a; }


protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Tools")
	TSubclassOf<ACRake> RakeClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Cursor")
	TSubclassOf<UUserWidget> CursorWidgetClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SkillWindowClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UCInventory> CInventoryClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UCItemWidget> InventoryWidgetClass;

	UPROPERTY(EditAnyWhere, Category = "Dialogue")
	TSubclassOf<class UCDialogueWidget> DialogueWidgetClass;

	UPROPERTY()
	class UCDialogueWidget* DialogueWidgetInstance;

	UPROPERTY()
	ACNpcone* LastInteractedNPC;

	UPROPERTY()
	class ACFlick* InteractedNPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionStimuliSourceComponent* StimuliSource;

	
	

private:

	UPROPERTY()
	UUserWidget* SkillWindowWidget;

	UCInventory* CInventoryWidget;

	UPROPERTY()
	UCItemWidget* ManageInventoryWidget;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;

	
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Tools")
	ACRake* Rake;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	bool IsVisible;

	

public:
	bool playanim;

private:
	int32 ItemIndex;

	bool shouldmove;

	int64 coin;
	
};
