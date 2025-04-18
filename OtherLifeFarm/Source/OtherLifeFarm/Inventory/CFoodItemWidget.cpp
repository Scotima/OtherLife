#include "Inventory/CFoodItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/Button.h"

void UCFoodItemWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UCFoodItemWidget::SetItemData(const FItemStruct& FoodData)
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

	

	if (FoodIconButton && FoodData.ItemIcon)
	{
		// 현재 버튼 스타일을 가져옵니다.
		FButtonStyle NewStyle = FoodIconButton->WidgetStyle;

		// 새 브러시를 생성하고 텍스처를 할당합니다.
		FSlateBrush NewBrush;
		NewBrush.SetResourceObject(FoodData.ItemIcon);
		// 필요에 따라 이미지 사이즈나 기타 브러시 속성을 설정할 수 있습니다.
		
		NewBrush.ImageSize = FVector2D(100.0f, 100.0f);

		// 각 상태에 대해 동일한 브러시를 적용합니다.
		NewStyle.Normal = NewBrush;
		NewStyle.Hovered = NewBrush;
		NewStyle.Pressed = NewBrush;

		// 변경된 스타일을 버튼에 적용합니다.
		FoodIconButton->SetStyle(NewStyle);
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



