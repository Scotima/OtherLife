
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inventory/FItemStruct.h"
#include "CCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACRake;
class UUserWidget;
class UCManageInventory;

UCLASS()
class OTHERLIFEFARM_API ACCharacter : public ACharacter
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


	void MouseLeft();

	void SetCustomMouseCursor();

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenWindowSkill();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void OpenInventory();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void PickupItem(FItemStruct NewItem);


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
	TSubclassOf<class UCManageInventory> InventoryWidgetClass;

private:

	UPROPERTY()
	UUserWidget* SkillWindowWidget;

	UCInventory* CInventoryWidget;

	UPROPERTY()
	UCManageInventory* ManageInventoryWidget;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Tools")
	ACRake* Rake;
	
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	bool IsVisible;

	
};
