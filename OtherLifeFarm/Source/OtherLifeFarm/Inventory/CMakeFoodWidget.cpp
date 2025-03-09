#include "Inventory/CMakeFoodWidget.h"
#include "Inventory/CFoodItemWidget.h"
#include "CMakeFoodWidget.h"

void UCMakeFoodWidget::NativeConstruct()
{
	FoodDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/FarmGame/DataTable/DT_Food"));

	if (!FoodDataTable)
	{
		UE_LOG(LogTemp, Error,TEXT("FoodDataTable is null"));
		return;
	}

	SetInven();
}

void UCMakeFoodWidget::ToogleInventory()
{
	bIsFoodWidgetOpen = !bIsFoodWidgetOpen;

	if (bIsFoodWidgetOpen)
	{
		this->SetVisibility(ESlateVisibility::Visible);

	}

	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCMakeFoodWidget::SetInven()
{
	if (!FoodDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("FoodDataTable is null"));
		return;
	}

	FoodData.Empty();
	FoodDataTable->GetAllRows<FItemStruct>(TEXT("DataTable Context"), FoodData);
	
	if (FoodItemArray.Num() < FoodData.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("FoodItemArray 크기가 부족합니다."));
		return;
	}

	for (int i = 0; i < FoodData.Num(); i++)
	{
		if (FoodItemArray.IsValidIndex(i))
		{
			FoodItemArray[i]->SetItemData(*FoodData[i]);
		}
	}

}
