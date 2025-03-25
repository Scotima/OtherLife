#include "StoreWidget/CStoreWidget.h"
#include"Inventory/CFoodItemWidget.h"

void UCStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UCStoreWidget::Sell(FItemStruct& fooditem)
{
	
}

void UCStoreWidget::StoreInven()
{
	if (!FoodorItemData)
	{
		UE_LOG(LogTemp, Error, TEXT("FoodorItemData is null"));
		return;
	}

	if (FoodData.Num() > 0)
	{
		FoodData.Empty();
	}

	const TMap<FName, uint8*>& RowMap = FoodorItemData->GetRowMap();
	static const FString ContextString(TEXT("FoodorItemData Context"));

	for (auto& RowPair : RowMap)
	{
		FItemStruct* Row = reinterpret_cast<FItemStruct*>(RowPair.Value);

		if (Row)
		{
			FoodData.Add(Row);
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Row is Null"));
		}

	}

	if (FoodItemArray.Num() < FoodData.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("FoodItem array size is not enough"));
	}

	for (int i = 0; i < FoodData.Num(); i++)
	{
		if (FoodItemArray.IsValidIndex(i))
		{
			FoodItemArray[i]->SetItemData(*FoodData[i]);
		}
	}



}
