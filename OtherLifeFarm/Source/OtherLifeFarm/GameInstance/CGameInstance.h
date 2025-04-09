
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


public:
	UPROPERTY(BlueprintReadWrite, Category = "FItemStructData")
	TArray<FItemStruct> Data;

	UPROPERTY(BlueprintReadWrite, Category = "Coin")
	int64 coin = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDestroyMode = false;

public:
	UFUNCTION(BlueprintCallable, Category = "FItemStructData")
	void AddData(FItemStruct item);

	UFUNCTION(BlueprintCallable, Category = "LoadData")
	void LoadRiceData();

	UFUNCTION(BlueprintCallable, Category = "Delete")
	void RemoveCropByLocation(FVector Location);
private:
	TArray<FCRiceStruct> SavedCrops;
	int32 spawnindex = 0;
public:
	void AddCrop(FCRiceStruct* item);


	
};
