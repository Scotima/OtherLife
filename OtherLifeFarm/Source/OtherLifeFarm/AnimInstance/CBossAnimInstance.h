#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CBossAnimInstance.generated.h"


UCLASS()
class OTHERLIFEFARM_API UCBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	FVector Velocity;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool ShouldMove;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	ACharacter* Character;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UCharacterMovementComponent* CharacterMovement;

	
};
