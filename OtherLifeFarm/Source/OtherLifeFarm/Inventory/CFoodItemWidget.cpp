#include "Inventory/CFoodItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"

void UCFoodItemWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UCFoodItemWidget::SetItemData(FItemStruct& FoodData)
{
	

	if (FoodNameText)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodNameText Succeess"));
		FoodNameText->SetText(FText::FromString(FoodData.ItemName));
		
		UE_LOG(LogTemp, Warning, TEXT("FoodNameText Succeessfully set : %s"), *FoodNameText->GetText().ToString());

	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("FoodNameText is null"));
	}

	

	if (FoodIconImage && FoodData.ItemIcon)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemIcon Succeess"));
		FoodIconImage->SetBrushFromTexture(FoodData.ItemIcon);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("ItemIcon is null"));
	}

	if (FoodNameCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodNameCount Succeess"));
		FoodNameCount->SetText(FText::AsNumber(FoodData.ItemCount));

		UE_LOG(LogTemp, Warning, TEXT("FoodNameCount Succeessfully set: %s"), *FoodNameCount->GetText().ToString());
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("FoodNameCount is null"));
	}

	this->SetVisibility(ESlateVisibility::Visible);
	SynchronizeProperties();


}

void UCFoodItemWidget::AddChildToPanel(UWidget* Widget)
{
	if (ItemPanel && Widget)
	{
		ItemPanel->AddChild(Widget);
		UE_LOG(LogTemp, Warning, TEXT("NewItemWidget added to InventoryPanel!!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ItemPanel or Widget is null"));
	}
}
