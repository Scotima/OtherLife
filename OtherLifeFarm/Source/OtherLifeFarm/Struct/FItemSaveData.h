#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FItemSaveData.generated.h"

USTRUCT(BlueprintType)
struct FItemSaveData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY()
	FString ItemName;

	UPROPERTY()
	int32 ItemCount;
	
};
