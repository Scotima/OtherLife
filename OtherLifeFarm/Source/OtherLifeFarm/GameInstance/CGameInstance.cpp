#include "GameInstance/CGameInstance.h"
#include "Inventory/CInventory.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/CFarmGameSave.h"
#include "Struct/CRiceStruct.h"
#include "Grain/CRice.h"
UCGameInstance::UCGameInstance()
{
	
}

void UCGameInstance::AddData(FItemStruct item)
{
	Data.Add(item);
}

void UCGameInstance::AddCrop(FCRiceStruct* ricedata)
{
	bool bUpdated = false;

	for (int32 i = 0; i < SavedCrops.Num(); ++i)
	{
		if (FVector::Dist(SavedCrops[i].CropLocation, ricedata->CropLocation) < 10.0f) // 10.0은 위치 허용 오차
		{
			SavedCrops[i] = *ricedata; // 기존 항목 덮어쓰기
			bUpdated = true;
			break;
		}
	}

	if (!bUpdated)
	{
		ricedata->Index = ++spawnindex;
		SavedCrops.Add(*ricedata); // 새로운 위치일 경우만 추가
	}

	// 저장 진행
	UCFarmGameSave* SaveGameInstance = Cast<UCFarmGameSave>(UGameplayStatics::CreateSaveGameObject(UCFarmGameSave::StaticClass()));

	SaveGameInstance->SavedCrops = SavedCrops;

	if (!SaveGameInstance->SavedCrops.IsEmpty())
	{
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySaveSlot"), 0);
	}
}

void UCGameInstance::LoadRiceData()
{

	UCFarmGameSave* LoadedGame = Cast<UCFarmGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveSlot"), 0));
	UWorld* world = GetWorld();
	if (LoadedGame)
	{
		if (world)
		{
			for (auto crop : LoadedGame->SavedCrops)
			{
				FActorSpawnParameters SpawnParams;

				ACRice* spawnrice = world->SpawnActor<ACRice>(ACRice::StaticClass(), crop.CropLocation, FRotator::ZeroRotator, SpawnParams);
				//SetActorLocation(crop.CropLocation);

				if (spawnrice)
				{
					spawnrice->SpawnSetting(crop.GrowthStage);
				}
			}
		}
	}
}

void UCGameInstance::RemoveCropByLocation(FVector Location)
{

	for (int32 i = 0; i < SavedCrops.Num(); ++i)
	{
		if (FVector::Dist(SavedCrops[i].CropLocation, Location) < 10.0f)
		{
			SavedCrops.RemoveAt(i);
			break;
		}
	}

	UCFarmGameSave* SaveGameInstance = Cast<UCFarmGameSave>(UGameplayStatics::CreateSaveGameObject(UCFarmGameSave::StaticClass()));
	SaveGameInstance->SavedCrops = SavedCrops;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySaveSlot"), 0);
}
