#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct : public FTableRowBase
{

	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ItemCount;

	FItemStruct()
	{
		ItemName = TEXT("Default");
		ItemIcon = nullptr;
		ItemCount = 1;

	}
};
