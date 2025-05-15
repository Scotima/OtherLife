#include "AnimNotify/CSpawnFlameEffectNotify.h"
#include"Skill/SplineFlameAttack.h"
#include"FarmCharacter/CBoss.h"

void UCSpawnFlameEffectNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animmation)
{
	if (!MeshComp)
	{
		return;
	}

	ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
	
	if (!boss || !boss->SplineFlameClass)
	{
		return;
	}

	FVector SpawnLocation = boss->GetActorLocation();
	FRotator SpawnRotation = boss->GetActorRotation();

	FActorSpawnParameters Params;
	Params.Instigator = boss;

	boss->GetWorld()->SpawnActor<ASplineFlameAttack>(boss->SplineFlameClass, SpawnLocation, SpawnRotation, Params);
}
