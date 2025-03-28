
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InterFace/CCharacterInterFace.h"
#include "CNpcone.generated.h"

class UCameraComponent;

UCLASS()
class OTHERLIFEFARM_API ACNpcone : public ACharacter, public ICCharacterInterFace
{
	GENERATED_BODY()

public:
	ACNpcone();

public:
	virtual UUserWidget* ShowWidget_Implementation() override;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void SetTalking(bool bTalking);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;


};
