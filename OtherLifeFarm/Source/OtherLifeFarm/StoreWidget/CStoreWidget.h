
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/FItemStruct.h"
#include "CStoreWidget.generated.h"

class UCFoodItemWidget;

UCLASS()
class OTHERLIFEFARM_API UCStoreWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "store")
	TArray<UCFoodItemWidget* > FoodItemArray;

private:
	TArray<FItemStruct> FoodData;

};
