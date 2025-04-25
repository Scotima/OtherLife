

#include "GhostGrain/CGhostRice.h"
#include "CGhostRice.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Grain/CRice.h"
#include "Tools/CRake.h"
#include "FarmCharacter/CCharacter.h"

// Sets default values
ACGhostRice::ACGhostRice()
{
	PrimaryActorTick.bCanEverTick = true;

	GhostRice = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GhostRice"));
	RootComponent = GhostRice;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GhostRiceAsset(TEXT("/Game/Environment/Meshes/Crops/SM_Crop_Wheat_01"));

	if (GhostRiceAsset.Succeeded())
	{
		GhostRice->SetStaticMesh(GhostRiceAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> GhostMaterial(TEXT("/Game/FarmGame/Material/M_GhostMaterial"));

	if (GhostMaterial.Succeeded())
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(GhostMaterial.Object, this);
		GhostRice->SetMaterial(0, DynamicMaterial);
	}

	RiceClass = nullptr;

}

void ACGhostRice::BeginPlay()
{
	Super::BeginPlay();
	isActive = true;
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		
		PlayerController->InputComponent->BindAction("MouseLeft", IE_Pressed, this, &ACGhostRice::RealSpawnRice);
		PlayerController->InputComponent->BindAction("Cancel", IE_Pressed, this, &ACGhostRice::Cancel);
	}


	

	character = Cast<ACCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));



	
}

void ACGhostRice::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (PlayerController)
	{
		if (PlayerController->InputComponent)
		{
			PlayerController->InputComponent->RemoveActionBinding("Cancel", IE_Pressed);
		}
	}
}

void ACGhostRice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetGhostLocation();

}

void ACGhostRice::SetGhostLocation()
{
	

	if (!PlayerController)
		return;

	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		SetActorLocation(HitResult.Location);
	}
}

void ACGhostRice::RealSpawnRice()
{

	if (!isActive)
		return;

	if (RiceClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("RiceClass is null"));
		return;
	}

	UWorld* World = GetWorld();

	if (World)
	{
		World->SpawnActor<ACRice>(RiceClass, GetActorLocation(), FRotator::ZeroRotator);



	}

	

}


void ACGhostRice::Cancel()
{

	UE_LOG(LogTemp, Warning, TEXT("Cancel"));
	this->Destroy();
	
	if (character)
	{
		character->playanim = true;
		return;
	}

	isActive = false;
}

