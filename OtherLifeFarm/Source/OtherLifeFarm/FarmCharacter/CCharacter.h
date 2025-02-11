
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACRake;
class UUserWidget;

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

	void OpenWindowSkill();

	void MouseLeft();

	void SetCustomMouseCursor();


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

private:

	UPROPERTY()
	UUserWidget* SkillWindowWidget;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Tools")
	ACRake* Rake;
	

};
