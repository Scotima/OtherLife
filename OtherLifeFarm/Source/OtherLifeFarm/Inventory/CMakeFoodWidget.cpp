#include "Inventory/CMakeFoodWidget.h"
#include "Inventory/CFoodItemWidget.h"
#include "CMakeFoodWidget.h"

void UCMakeFoodWidget::NativeConstruct()
{
	FoodDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/FarmGame/DataTable/DT_Food"));

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
		UE_LOG(LogTemp, Error, TEXT("")); // Todo 배열 이어서 마저 작성하기.
	}

}
