#include "Grain/CRice.h"
#include "FarmCharacter/CCharacter.h"
#include "SaveGame/CFarmGameSave.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/CGameInstance.h"

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
	//LoadRiceData();

	//SaveRiceData();
}

void ACRice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACRice::SaveRiceData()
{
	UCGameInstance* gameinstance = Cast<UCGameInstance>(GetGameInstance());

	if (gameinstance)
	{

		ricedata.CropLocation = GetActorLocation();
		
		ricedata.GrowthStage = FMath::Clamp(CurrentMeshIndex, 0, RiceMeshs.Num() - 1);
		
		gameinstance->AddCrop(&ricedata);



	}
	






}

void ACRice::LoadRiceData()
{

	//UCFarmGameSave* LoadedGame = Cast<UCFarmGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveSlot"), 0));
	//UWorld* world = GetWorld();
	//if (LoadedGame)
	//{
	//	if(world)
	//	{ 
	//		for (auto crop : LoadedGame->SavedCrops)
	//		{
	//			FActorSpawnParameters SpawnParams;
	//			SpawnParams.Owner = this;

	//			ACRice* spawnrice = world->SpawnActor<ACRice>(ACRice::StaticClass(), crop.CropLocation, FRotator::ZeroRotator, SpawnParams);
	//			//SetActorLocation(crop.CropLocation);

	//			if (spawnrice)
	//			{
	//				SetCurrentMeshIndex(crop.GrowthStage);
	//				RiceMesh->SetStaticMesh(RiceMeshs[CurrentMeshIndex]);
	//				SetGrowing();

	//			}
	//			

	//			

	//		}
	//	}
	//}

	/*UCGameInstance* gameinstance = Cast<UCGameInstance>(GetGameInstance());

	if (gameinstance)
	{
		gameinstance->LoadRiceData();
	}*/

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

void ACRice::RemoveMe()
{
	if (UCGameInstance* gameinstance = Cast<UCGameInstance>(GetGameInstance()))
	{
		gameinstance->RemoveCropByLocation(GetActorLocation());
	}

	Destroy();
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

		SaveRiceData();

	CurrentMeshIndex++;

	if (CurrentMeshIndex >= RiceMeshs.Num())
	{
		GetWorldTimerManager().ClearTimer(ChangeMeshTimerHandle);
		UE_LOG(LogTemp, Log, TEXT("Rice is fully grown! Timer Stopped."));
	}
}

void ACRice::SpawnSetting(int32 GrowthStage)
{
	SetCurrentMeshIndex(GrowthStage);
	RiceMesh->SetStaticMesh(RiceMeshs[GrowthStage]);
	SetGrowing();
	//CurrentMeshIndex = GrowthStage;
}

