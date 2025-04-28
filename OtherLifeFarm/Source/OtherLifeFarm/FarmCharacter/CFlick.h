// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InterFace/CCharacterInterFace.h"
#include "CFlick.generated.h"

UCLASS()
class OTHERLIFEFARM_API ACFlick : public ACharacter, public ICCharacterInterFace
{
	GENERATED_BODY()

public:
	ACFlick();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	void StartTalking();

	void StopTalking();
public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsTalking = false;

};
