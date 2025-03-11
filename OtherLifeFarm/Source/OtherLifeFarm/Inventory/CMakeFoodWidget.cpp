#include "Inventory/CMakeFoodWidget.h"
#include "Inventory/CFoodItemWidget.h"
#include "Blueprint/UserWidget.h"
#include "CMakeFoodWidget.h"
#include "Components/CanvasPanelSlot.h"


void UCMakeFoodWidget::NativeConstruct()
{
	FoodDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/FarmGame/DataTable/DT_Food"));

	

	

	

	if (!FoodDataTable)
	{
		UE_LOG(LogTemp, Error,TEXT("FoodDataTable is null"));
		return;
	}

	
}

void UCMakeFoodWidget::ToogleInventory()
{
	bIsFoodWidgetOpen = !bIsFoodWidgetOpen;

	SetInven();

	//SetVisibility(bIsFoodWidgetOpen ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if (bIsFoodWidgetOpen )
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
		{
			CanvasSlot->SetZOrder(10);
		}

		
	}
	else
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
		{
			CanvasSlot->SetZOrder(1);
		}
	}
}

void UCMakeFoodWidget::SetInven()
{
	if (!FoodDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("FoodDataTable is null"));
		return;
	}
	//FoodData = new TArray<FItemStruct*>();
	if (FoodData.Num() > 0)
	{
		FoodData.Empty(); 
	}

	FoodDataTable->GetAllRows<FItemStruct>(TEXT("DataTable Context"), FoodData);

	


	for (int i = 0; i < FoodData.Num(); i++)
	{
		if (FoodItemArray.IsValidIndex(i))
		{
			FoodItemArray[i]->SetItemData(*FoodData[i]);
		}
	}
	
	if (FoodItemArray.Num() < FoodData.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Food item array size is not enough"));
		return;
	}



}
