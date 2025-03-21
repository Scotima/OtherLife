#include "Tools/CRake.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "FarmCharacter/CCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Grain/CRice.h"


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

	//static ConstructorHelpers::FObjectFinder<UAnimMontage> RakeAssetMontageClass(TEXT("/Game/FarmGame/BPCharacter/CharacterAsset/Boy/Anim/BOY_Farmer_work_Hoe_Montage"));

	//if (RakeAssetMontageClass.Succeeded())
	//{
	//	RakeAssetMontage = RakeAssetMontageClass.Object;
	//}
	

	HandSocket = "hand_rsocket";

}

void ACRake::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACCharacter>(GetOwner());

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{

		PlayerController->InputComponent->BindAction("MouseLeft", IE_Pressed, this, &ACRake::Plowing);
	}


	
	
}

void ACRake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRake::Plowing()
{
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("OwnerCharacter is null in Plowing!"));
		return;
	}

	if (!RakeAssetMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("RakeAssetMontage is null in Plowing!"));
		return;
	}
	if (Character->playanim == true)
	{
		OwnerCharacter->PlayAnimMontage(RakeAssetMontage);
		TurnToMouse();
		SweepSingleByChannel();
		
		
	}

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

	TArray<FHitResult> HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	



	bool bHit = UKismetSystemLibrary::SphereTraceMulti(
		GetWorld(), End, End, SphereRadius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 1.f);


	for (const FHitResult& hitresult : HitResult)
	{
		if(bHit)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *hitresult.GetActor()->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Ignoring %d actors"), ActorsToIgnore.Num());
			UE_LOG(LogTemp, Warning, TEXT("Total Hit Count: %d"), HitResult.Num());
		}

		if (bHit)
		{
			UStaticMeshComponent* HitComponent = Cast<UStaticMeshComponent>(hitresult.GetComponent());
			if(HitComponent)
			{ 
				rice = Cast<ACRice>(hitresult.GetActor());
				if (rice)
				{
					rice->GoToInventory();
					rice->SetCurrentMeshIndex(0);
					rice->RiceMesh->SetStaticMesh(rice->RiceMeshs[rice->GetCurrentMeshIndex()]);
					rice->SetGrowing();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("rice casting failed"));
				}
			}

		}
	}
	

	
}

void ACRake::TurnToMouse()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PC)
	{
		return;
	}
	FVector WorldLocation, WorldDirection;

	if (PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{

		FHitResult HitResult;
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 10000.f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
		{
			FVector MouseWorldPosition = HitResult.Location;
			FRotator LookAtRotation = (MouseWorldPosition - GetActorLocation()).Rotation();
			LookAtRotation.Pitch = 0.f; // Y축 고정
			OwnerCharacter = Cast<ACCharacter>(GetOwner());
			if (!OwnerCharacter) return;
			OwnerCharacter->SetActorRotation(LookAtRotation);
		}

	}
}

void ACRake::AttachToOwner()
{

	OwnerCharacter = Cast<ACCharacter>(GetOwner());
	if (!OwnerCharacter || !RakeMesh) return;

	if (OriginalLocation.IsZero() && OriginalRotation.IsZero())
	{
		OriginalLocation = GetActorLocation();
		OriginalRotation = GetActorRotation();
	}

	// Attach to the character's mesh
	AttachToComponent(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		HandSocket
	);

	// Configure RakeMesh properties
	//RakeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//RakeMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
	//RakeMesh->SetRelativeRotation(FRotator(0.f, -100.f, -180.0f));
	
	
	if (Character)
	{
		Character->playanim = true;
	}
	

	UE_LOG(LogTemp, Log, TEXT("Rake attached to the owner."));
}

void ACRake::DetachFromOwner()
{
	if (!OwnerCharacter || !RakeMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rake or OwnerCharacter is NULL! Cannot detach."));
		return;
	}

	DetachFromActor((FDetachmentTransformRules::KeepWorldTransform));

	// Rake를 원래 위치로 이동
	SetActorLocation(OriginalLocation);
	SetActorRotation(OriginalRotation);

	UE_LOG(LogTemp, Log, TEXT("Rake detached and returned to original position."));

	

	if (Character)
	{
		Character->playanim = false;
	}


}

