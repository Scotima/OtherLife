#include "AnimInstance/CBossAnimInstance.h"
#include "CBossAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void UCBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());

	if (Character)
	{

		CharacterMovement = Character->GetCharacterMovement();
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("UCBossAnimInstance -> Character is null"));
	}


	ShouldMove = false;
}

void UCBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!TryGetPawnOwner()) // 만약 캐릭터가 없다면 중단
	{
		return;
	}

	if (!CharacterMovement)
	{
		return; // 만약에 캐릭터무브먼트가 없을경우 오류 방지.
	}

	Velocity = CharacterMovement-> Velocity;

	GroundSpeed = Velocity.Size2D();

	if (GroundSpeed > 3.0f)
	{
		ShouldMove = true;
	}

	else
	{
		ShouldMove = false;
	}
}
