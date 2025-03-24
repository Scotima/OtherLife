// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/CMoveNotify.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCMoveNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animmation)
{
	if (!MeshComp)
	{
		return;
	}

	ownercharacter = Cast<ACharacter>(MeshComp->GetOwner());

	if (!ownercharacter)
	{
		return;
	}

	if (!ownercharacter->GetCharacterMovement())
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterMovementComponent is NULL in UCStopNotify::Notify"));
		return;
	}

	ownercharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}
