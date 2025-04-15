#include "GameInstance/CGameInstance.h"
#include "Inventory/CInventory.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/CFarmGameSave.h"
#include "Struct/CRiceStruct.h"
#include "Grain/CRice.h"
#include "TimerManager.h" 
UCGameInstance::UCGameInstance()
{
	
}

void UCGameInstance::Init()
{
	Super::Init();
	StartPriceTimer();
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

	UCFarmGameSave* SaveGameInstance = Cast<UCFarmGameSave>(UGameplayStatics::CreateSaveGameObject(UCFarmGameSave::StaticClass()));
	SaveGameInstance->SavedCrops = SavedCrops;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySaveSlot"), 0);
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

void UCGameInstance::RefreshPrices()
{
	CurrentPrices.Add(FMath::RandRange(1000, 3000));
	CurrentPrices.Add(FMath::RandRange(1000, 3000));
	CurrentPrices.Add(FMath::RandRange(1000, 3000));
}
