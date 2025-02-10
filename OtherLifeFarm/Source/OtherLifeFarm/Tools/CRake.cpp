#include "Tools/CRake.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"

ACRake::ACRake()
{
	PrimaryActorTick.bCanEverTick = true;

	RakeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RakeMesh"));
	RootComponent = RakeMesh;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> RakeMeshAsset(TEXT("/Game/3D_LOW_POLY_FarmerPack/Props/SM_Rake"));

	if (RakeMeshAsset.Succeeded())
	{
		RakeMesh->SetStaticMesh(RakeMeshAsset.Object);
	}

	RakeMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("RakeMontage"));

	ConstructorHelpers::FObjectFinder<UAnimMontage> RakeMontageAsset(TEXT("/Game/FarmGame/Animation/anim_Farmer_work_Hoe_Montage"));

	if (RakeMontageAsset.Succeeded())
	{
		RakeMontage = RakeMontageAsset.Object;
	}
	

	RakeSocketName = "middle_02_rsocket";

}

void ACRake::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACRake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRake::AttachToOwner()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (!OwnerCharacter || !RakeMesh)
		return;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), RakeSocketName);

	if (RakeMesh)
	{
		RakeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// 상대 위치 설정
		RakeMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
		RakeMesh->SetRelativeRotation(FRotator(0.f, -187.f, 0.f));
	}

}



void ACRake::Plowing()
{
	OwnerCharacter->PlayAnimMontage(RakeMontage);
}

void ACRake::SweepSingleByChannel()
{
	FVector Start = OwnerCharacter->GetActorLocation();
	FRotator ActorRotation = OwnerCharacter->GetActorRotation();
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ActorRotation);
	double Multiplier = 100.f;

	FVector MultipliedVector = ForwardVector * Multiplier;
	FVector End = Start + MultipliedVector;
	float SphereRadius = 100.f;

	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);



	bool bHit = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(), End, End, SphereRadius, UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1), false, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 1.f);

	if (bHit)
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());

	}

	
}

