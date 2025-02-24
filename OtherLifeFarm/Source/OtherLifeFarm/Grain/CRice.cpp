#include "Grain/CRice.h"
#include "FarmCharacter/CCharacter.h"
#include "Kismet/GameplayStatics.h"

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

	// RiceMesh의 충돌 설정 추가
	RiceMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // 물리 연산 없이 충돌 감지만
	RiceMesh->SetCollisionObjectType(ECC_WorldDynamic); // 동적 오브젝트로 설정
	RiceMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	RiceMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // 트레이스 감지를 위해 Visibility만 Block

	
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

void ACRice::GoToInventory()
{
	ACCharacter* character = Cast<ACCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (character)
	{
		character->PickupItem(ItemData);
	}
}

void ACRice::SetGrowing()
{
	GetWorldTimerManager().SetTimer(ChangeMeshTimerHandle, this, &ACRice::GrowRice, 2.0f, true);
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

