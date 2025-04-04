#include "GameInstance/CGameInstance.h"
#include "Inventory/CInventory.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/CFarmGameSave.h"
#include "Struct/CRiceStruct.h"

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

