
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

public:
	UFUNCTION(BlueprintCallable, Category = "FItemStructData")
	void AddData(FItemStruct item);

private:
	TArray<FCRiceStruct> SavedCrops;

public:
	void AddCrop(FCRiceStruct* item);



	
};
