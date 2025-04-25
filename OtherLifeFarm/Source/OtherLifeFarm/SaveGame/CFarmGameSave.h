// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Struct/CRiceStruct.h"
#include "Inventory/FItemStruct.h"
#include "Struct/FItemSaveData.h"
#include "CFarmGameSave.generated.h"


UCLASS()
class OTHERLIFEFARM_API UCFarmGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FCRiceStruct> SavedCrops;

	UPROPERTY(VisibleAnywhere, Category = "SaveData")
	TArray<FItemSaveData> SavedData;
	
};
