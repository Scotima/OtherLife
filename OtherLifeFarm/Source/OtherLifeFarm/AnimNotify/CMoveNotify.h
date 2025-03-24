// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CMoveNotify.generated.h"

class ACharacter;

UCLASS()
class OTHERLIFEFARM_API UCMoveNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animmation) override;
	

private:
	ACharacter* ownercharacter;
};
