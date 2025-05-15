#include "FarmCharacter/CBoss.h"
#include "Animation/AnimMontage.h"
#include "Skill/SplineFlameAttack.h"
ACBoss::ACBoss()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

