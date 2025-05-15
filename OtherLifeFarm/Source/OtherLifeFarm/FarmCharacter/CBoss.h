
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBoss.generated.h"

class UAnimMontage;

UCLASS()
class OTHERLIFEFARM_API ACBoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACBoss();


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* MeleeAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* JumpSmashMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<class ASplineFlameAttack> SplineFlameClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
