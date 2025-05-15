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
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;

}

void ASplineFlameAttack::BeginPlay()
{
	Super::BeginPlay();
	if (!FlameEffect || !Spline)
	{
		UE_LOG(LogTemp, Warning, TEXT("나이아가라 이펙트나 스플라인이 없음"));
		return;
	}


	NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(), FlameEffect, Spline->GetLocationAtDistanceAlongSpline(0.f, ESplineCoordinateSpace::World), FRotator::ZeroRotator,FVector(3.f, 3.f, 3.f)
	);
	NiagaraComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	Spline->ClearSplinePoints();

	FVector StartLocation = GetActorLocation();
	FVector Direction = GetActorForwardVector();

	for (int32 i = 0; i < 10; ++i)
	{
		FVector PointLocation = StartLocation + Direction * (i * 200.f);
		Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
	}
	Spline->UpdateSpline();
}

void ASplineFlameAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Spline || !NiagaraComp) return;

	TravelDistance += DeltaTime * Speed;

	float SplineLength = Spline->GetSplineLength();

	if (TravelDistance > SplineLength)
	{
		NiagaraComp->Deactivate();
		Destroy(); // 또는 SetLifeSpan
		return;
	}

	FVector NewLocation = Spline->GetLocationAtDistanceAlongSpline(TravelDistance, ESplineCoordinateSpace::World);
	NiagaraComp->SetWorldLocation(NewLocation);

}



