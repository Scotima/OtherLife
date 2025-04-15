
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Inventory/FItemStruct.h"
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

	UPROPERTY(BlueprintReadWrite, Category = "Coin")
	int64 coin = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDestroyMode = false;

	UPROPERTY(BlueprintReadOnly)
	float RemainingTime;

	UPROPERTY(BlueprintReadOnly)
	TArray<int64> CurrentPrices;
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

private:
	UFUNCTION()
	void RefreshPrices();
private:
	TArray<FCRiceStruct> SavedCrops;
	int32 spawnindex = 0;
	FTimerHandle TimerHandle;

public:
	void AddCrop(FCRiceStruct* item);


	
};
