#include "GameInstance/CGameInstance.h"
#include "Inventory/CInventory.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/CFarmGameSave.h"
#include "Struct/CRiceStruct.h"
#include "Struct/FAllItem.h"
#include "Grain/CRice.h"
#include "TimerManager.h" 
UCGameInstance::UCGameInstance()
{
	
}

void UCGameInstance::Init()
{
	Super::Init();
	StartPriceTimer();
	RefreshPrices();

	FoodDataTable = LoadObject<UDataTable>(this, TEXT("/Game/FarmGame/DataTable/DT_Food"));

	AllItemData = LoadObject<UDataTable>(nullptr, TEXT("/Game/FarmGame/Data/DT_AllItem.DT_AllItem"));


	

	if (FoodDataTable)
	{
		TArray<FItemStruct*> TempRows;

		FoodDataTable->GetAllRows<FItemStruct>(TEXT("FoodTableLoad"), TempRows);

		CachedFoodData.Empty();

		for (FItemStruct* Row : TempRows)
		{
			CachedFoodData.Add(*Row);
		}
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load FoodDataTable in GameInstance"));
	}


	if (AllItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("AllItemData Load Success"));

		TArray<FAllItem*> AllRows;

		AllItemData->GetAllRows<FAllItem>(TEXT("LoadAllItems"), AllRows);
		

		for(FAllItem* Row : AllRows)
		{
			if (Row)
			{
				UTexture2D* Icon = Cast<UTexture2D>(Row->IconPath.TryLoad());

				if (!Icon)
				{
					UE_LOG(LogTemp, Error, TEXT("Icon Load Failed : %s"), *Row->ItemID.ToString());
				}
				ItemIconMap.Add(Row->ItemID, Icon);
			}
		}

	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AllItemData Load Failed"));

	}


}

void UCGameInstance::AddData(FItemStruct item)
{
	Data.Add(item);

	SaveInventoryData(Data);
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
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("CropSlot"), 0);
	}
}

const TArray<FItemStruct>& UCGameInstance::GetFoodData() const
{
	 return CachedFoodData;
}

void UCGameInstance::LoadRiceData()
{

	UCFarmGameSave* LoadedGame = Cast<UCFarmGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("CropSlot"), 0));
	UWorld* world = GetWorld();

	if (LoadedGame)
	{
		if (world)
		{
			for (auto crop : LoadedGame->SavedCrops)
			{
				UClass* RiceClass = crop.RiceClass.TryLoadClass<ACRice>();

				if (RiceClass)
				{

					FActorSpawnParameters SpawnParams;

					ACRice* spawnrice = world->SpawnActor<ACRice>(RiceClass, crop.CropLocation, FRotator::ZeroRotator, SpawnParams);

					if (spawnrice)
					{
						spawnrice->SpawnSetting(crop.GrowthStage);
					}
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

	UCFarmGameSave* SaveGameInstance = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(TEXT("CropSlot"), 1))
	{
		SaveGameInstance = Cast<UCFarmGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("CropSlot"), 1));
	}

	else
	{
		SaveGameInstance = Cast<UCFarmGameSave>(UGameplayStatics::CreateSaveGameObject(UCFarmGameSave::StaticClass()));
	}

	if (!SaveGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load or create SaveGameInstance in RemoveCropByLocation"));
	}

	SaveGameInstance->SavedCrops = SavedCrops;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("CropSlot"), 0);
}

void UCGameInstance::StartPriceTimer()
{
	RemainingTime = 1800.0f;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCGameInstance::UpdateTimer, 1.0f, true);
}

void UCGameInstance::UpdateTimer()
{
	RemainingTime -= 1.0f;

	if (RemainingTime <= 0.0f)
	{
		RemainingTime = 1800.0f;
		RefreshPrices();
	}
}

void UCGameInstance::SaveInventoryData(TArray<FItemStruct>& item)
{

	UCFarmGameSave* SaveGameInstance = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(TEXT("InventorySlot"), 1))
	{
		SaveGameInstance = Cast<UCFarmGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveSlot"), 1));
	}

	else
	{
		SaveGameInstance = Cast<UCFarmGameSave>(UGameplayStatics::CreateSaveGameObject(UCFarmGameSave::StaticClass()));
	}

	if (!SaveGameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create or load SaveGameInstance"));
		return;
	}

	SaveGameInstance->SavedData = ConvertToSaveData(item);
	

	if (!SaveGameInstance->SavedData.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Saving %d items"), item.Num());
		UE_LOG(LogTemp, Warning, TEXT("Saved %d Items to slot 1"), SaveGameInstance->SavedData.Num());
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("InventorySlot"), 1);
	}


}

const TArray<FItemStruct>UCGameInstance::LoadInventoryData()
{
	
	
	TArray<FItemStruct> RestoredInventory;

	UCFarmGameSave* LoadedGame = Cast<UCFarmGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("InventorySlot"), 1));

	if (!LoadedGame)
	{
		UE_LOG(LogTemp, Error, TEXT("LoadInventoryData failed: save file not found"));
		RestoredInventory.Empty();
		return RestoredInventory;
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("SaveData : %d"), LoadedGame->SavedData.Num());
	}

	RestoredInventory = ConvertToItemStruct(LoadedGame->SavedData);

	if (!RestoredInventory.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("RestoredInventory : %d"), RestoredInventory.Num());
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("RestiredInventory is empty"));
	}

	return RestoredInventory;
	
	
	
}

//저장용 변환 (FItemStruct -> FItemSaveData)
TArray<FItemSaveData> UCGameInstance::ConvertToSaveData(const TArray<FItemStruct>& Source)
{
	TArray<FItemSaveData> Result;

	for (const FItemStruct& Item : Source)
	{
		FItemSaveData SaveItem;
		SaveItem.ItemName = Item.ItemName;
		SaveItem.ItemCount = Item.ItemCount;

		Result.Add(SaveItem);

	}

	return Result;
}

// 불러오기용 복원 (FItemSaveData->FItemStruct)
TArray<FItemStruct> UCGameInstance::ConvertToItemStruct(const TArray<FItemSaveData>& Source)
{
	TArray<FItemStruct> Result;

	for (const FItemSaveData& SaveItem : Source)
	{
		FItemStruct Item;
		Item.ItemName = SaveItem.ItemName;
		Item.ItemCount = SaveItem.ItemCount;

		FName IconKey = FName(Item.ItemName);

		if (ItemIconMap.Contains(IconKey))
		{
			Item.ItemIcon = ItemIconMap[IconKey];
		}

		else
		{
			Item.ItemIcon = nullptr;
		}

		Result.Add(Item);
	}

	return Result;

}

void UCGameInstance::RefreshPrices()
{
	CurrentPrices.Add(FMath::RandRange(1000, 3000));
	CurrentPrices.Add(FMath::RandRange(1000, 3000));
	CurrentPrices.Add(FMath::RandRange(1000, 3000));

	BuyPrices.Add(FMath::RandRange(1000, 3000));
	BuyPrices.Add(FMath::RandRange(1000, 3000));
	BuyPrices.Add(FMath::RandRange(1000, 3000));
}
