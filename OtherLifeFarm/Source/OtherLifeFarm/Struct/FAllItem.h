
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FAllItem.generated.h"


USTRUCT(BlueprintType)
struct FAllItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID; // 고유 ID

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FText ItemDescription;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 ItemValue;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FSoftObjectPath IconPath; // 저장용 텍스처 경로

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UTexture2D* PreviewIcon; // 디자이너 미리 보기 용
	
};
