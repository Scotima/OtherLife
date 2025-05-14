#include "Skill/SplineFlameAttack.h"
#include "Components/SplineComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "TimerManager.h"


ASplineFlameAttack::ASplineFlameAttack()
{
	PrimaryActorTick.bCanEverTick = false;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;

}

void ASplineFlameAttack::BeginPlay()
{
	Super::BeginPlay();

	Spline->ClearSplinePoints();//직진
	FVector Start = GetActorLocation();
	FVector Direction = GetActorForwardVector();

	for (int32 i = 0; i < NumPoints; ++i)
	{
		Spline->AddSplinePoint(Start + Direction * (i * Spacing), ESplineCoordinateSpace::World);
	}

	CurrentSpawnIndex = 0;
	GetWorldTimerManager().SetTimer(FlameSpawnTimerHandle, this, &ASplineFlameAttack::SpawnNextFlame, FlameSpawnInterval, true);
	
}

void ASplineFlameAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASplineFlameAttack::SpawnFlameAlongSpline()
{
	if (!FlameEffect) return;

	for (int32 i = 0; i < NumPoints; ++i)
	{
		FVector Location = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FlameEffect, Location);

		//타격판정
		TArray<FHitResult> Hits;
		FCollisionShape Shape = FCollisionShape::MakeSphere(50.f);
		bool bHit = GetWorld()->SweepMultiByChannel(Hits, Location, Location + FVector(0.1f), FQuat::Identity, ECC_Pawn, Shape);

		if (bHit)
		{
			for (auto& Hit : Hits)
			{
				AActor* HitActor = Hit.GetActor();
				if (HitActor && HitActor != this)
				{
					UGameplayStatics::ApplyDamage(HitActor, Damage, GetInstigatorController(), this, DamageType);
				}
			}
		}
		
	}
}

void ASplineFlameAttack::SpawnNextFlame()
{
	if (!FlameEffect || CurrentSpawnIndex >= NumPoints)
	{
		GetWorldTimerManager().ClearTimer(FlameSpawnTimerHandle);

		UE_LOG(LogTemp, Warning, TEXT("파괴 시도!."));
		Destroy();
		return;
	}

	FVector Location = Spline->GetLocationAtSplinePoint(CurrentSpawnIndex, ESplineCoordinateSpace::World);
	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		FlameEffect,
		Location,
		FRotator::ZeroRotator,
		FVector(1.f),
		true, // auto Destroy
		false,//autoActivate false 수동모드
		ENCPoolMethod::None,
		false // precullcheck
	);

	if (NiagaraComp)
	{
		NiagaraComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	}

	TArray<FHitResult> Hits;
	FCollisionShape Shape = FCollisionShape::MakeSphere(50.f);

	bool bHit = GetWorld()->SweepMultiByChannel(Hits, Location, Location + FVector(0.1f), FQuat::Identity, ECC_Pawn, Shape);


	if (bHit)
	{
		for (auto& Hit : Hits)
		{
			AActor* HitActor = Hit.GetActor();

			if (HitActor)
			{
				UGameplayStatics::ApplyDamage(HitActor, Damage, GetInstigatorController(), this, DamageType);

			}
		}
	}

	++CurrentSpawnIndex;
}

