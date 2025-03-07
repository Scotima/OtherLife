
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FItemStruct.h"
#include "CMakeFoodWidget.generated.h"

class UCFoodItemWidget;

UCLASS()
class OTHERLIFEFARM_API UCMakeFoodWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	FORCEINLINE bool GetFoodInventoryOpen() { return bIsFoodWidgetOpen; }
	FORCEINLINE void SetFoodInventoryOpen(bool a) { bIsFoodWidgetOpen = a; }

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void ToogleInventory();

protected:
	void SetInven();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<UCFoodItemWidget* > FoodItemArray;

	TArray<FItemStruct*> FoodData;

private:
	UDataTable* FoodDataTable;

private:
	bool bIsFoodWidgetOpen;

	
	
};
