// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/CStopNotify.h"
#include "CStopNotify.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCStopNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

	ownercharacter->GetCharacterMovement()->SetMovementMode(MOVE_None);


}
