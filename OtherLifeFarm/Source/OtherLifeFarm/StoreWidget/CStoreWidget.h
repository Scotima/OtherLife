
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/FItemStruct.h"
#include "CStoreWidget.generated.h"

class UCFoodItemWidget;
class ACCharacter;

UCLASS()
class OTHERLIFEFARM_API UCStoreWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;


public:
	UFUNCTION(BlueprintCallable, Category = "store")
	void Sell(FItemStruct& fooditem);

	UFUNCTION(BlueprintCallable, Category = "Inven")
	void StoreInven();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "store")
	TArray<UCFoodItemWidget*> FoodItemArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = "true"))
	UDataTable* FoodorItemData;


private:
	TArray<FItemStruct*> FoodData;
	ACCharacter* character;
};
