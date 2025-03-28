// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CNpconeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class OTHERLIFEFARM_API UCNpconeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SetTalking(bool bTalk) { bIsTalking = bTalk; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	bool bIsTalking;

	
};
