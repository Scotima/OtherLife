
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Inventory/FItemStruct.h"
#include "Struct/FItemSaveData.h"
#include "CGameInstance.generated.h"

struct FCRiceStruct;

class UCInventory;
class UCFarmGameSave;


UCLASS()
class OTHERLIFEFARM_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UCGameInstance();

	virtual void Init() override;

public:
	UPROPERTY(BlueprintReadWrite, Category = "FItemStructData")
	TArray<FItemStruct> Data;

	UPROPERTY()
	TMap<FName, UTexture2D*> ItemIconMap;

	UPROPERTY(BlueprintReadWrite, Category = "Coin")
	int64 coin = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDestroyMode = false;

	UPROPERTY(BlueprintReadOnly)
	float RemainingTime;

	UPROPERTY(BlueprintReadOnly)
	TArray<int64> CurrentPrices;

	UPROPERTY(BlueprintReadOnly)
	TArray<int64> BuyPrices;

	UPROPERTY()
	UDataTable* FoodDataTable;

	UPROPERTY()
	UDataTable* AllItemData;

	UPROPERTY()
	TArray<FItemStruct> CachedFoodData;

	UPROPERTY()
	UCInventory* intentory;

public:
	UFUNCTION(BlueprintCallable, Category = "FItemStructData")
	void AddData(FItemStruct item);

	UFUNCTION(BlueprintCallable, Category = "LoadData")
	void LoadRiceData();

	UFUNCTION(BlueprintCallable, Category = "Delete")
	void RemoveCropByLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void StartPriceTimer();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	void UpdateTimer();

	UFUNCTION(BlueprintCallable, Category = "SaveInventoryData")
	void SaveInventoryData(TArray<FItemStruct>& item);

	UFUNCTION(BlueprintCallable, Category = "LoadInventoryData")
	const TArray<FItemStruct> LoadInventoryData();


protected:
	// 저장용으로 변환 (게임 -> 저장)
	TArray<FItemSaveData> ConvertToSaveData(const TArray<FItemStruct>& Source);

	//저장된 데이터를 복원(저장->게임)

	TArray<FItemStruct> ConvertToItemStruct(const TArray<FItemSaveData>& Source);




private:
	UFUNCTION()
	void RefreshPrices();
private:
	TArray<FCRiceStruct> SavedCrops;
	int32 spawnindex = 0;
	FTimerHandle TimerHandle;

public:
	void AddCrop(FCRiceStruct* item);

	const TArray<FItemStruct>& GetFoodData() const;



	
};
