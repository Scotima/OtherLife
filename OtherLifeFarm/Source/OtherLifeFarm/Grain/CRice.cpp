#include "Grain/CRice.h"

ACRice::ACRice()
{
	PrimaryActorTick.bCanEverTick = true;

	RiceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RiceMesh"));
	RootComponent = RiceMesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> RiceMeshAsset0(TEXT("/Game/Environment/Meshes/Crops/SM_Crop_Wheat_01"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> RiceMeshAsset1(TEXT("/Game/Environment/Meshes/Crops/SM_Crop_Wheat_02"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> RiceMeshAsset2(TEXT("/Game/Environment/Meshes/Crops/SM_Crop_Wheat_03"));

	if (RiceMeshAsset0.Succeeded() && RiceMeshAsset1.Succeeded() && RiceMeshAsset2.Succeeded())
	{
		RiceMeshs.Add(RiceMeshAsset0.Object);
		RiceMeshs.Add(RiceMeshAsset1.Object);
		RiceMeshs.Add(RiceMeshAsset2.Object);

		RiceMesh->SetStaticMesh(RiceMeshs[0]);
	}

	CurrentMeshIndex = 0;

}

void ACRice::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ChangeMeshTimerHandle, this, &ACRice::GrowRice, 2.0f, true);
}

void ACRice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRice::GrowRice()
{

	if (RiceMeshs.Num() == 0 || !RiceMeshs.IsValidIndex(CurrentMeshIndex))
	{
		GetWorldTimerManager().ClearTimer(ChangeMeshTimerHandle);
		UE_LOG(LogTemp, Error, TEXT("MeshAsset is empty or CurrentStateIndex is out of range. Timer Stopped."));

		return;
	}

	RiceMesh->SetStaticMesh(RiceMeshs[CurrentMeshIndex]);

	CurrentMeshIndex++;

	if (CurrentMeshIndex >= RiceMeshs.Num())
	{
		GetWorldTimerManager().ClearTimer(ChangeMeshTimerHandle);
		UE_LOG(LogTemp, Log, TEXT("Rice is fully grown! Timer Stopped."));
	}
}

