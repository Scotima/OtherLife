#pragma once

#include "CoreMinimal.h"
//#include "StructUtils/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "CRiceStruct.generated.h"

USTRUCT(BlueprintType)
struct FCRiceStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Crop")
	FVector CropLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Crop")
	int32 GrowthStage;

	
	FCRiceStruct()
	:CropLocation(FVector::ZeroVector)
	,GrowthStage(0)
	{}



	
};
