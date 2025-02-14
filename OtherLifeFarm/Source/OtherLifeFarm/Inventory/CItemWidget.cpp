#include "Inventory/CItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UCItemWidget::SetItemData(const FItemStruct& ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("SetItemData Succeess"));

	UE_LOG(LogTemp, Log, TEXT("SetItemData called - Name: %s, Count: %d"),
		*ItemData.ItemName, ItemData.ItemCount);

	if (ItemNameText)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemNameText is not null"))
		ItemNameText->SetText(FText::FromString(ItemData.ItemName));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemNameText is  null"));
	}

	if (ItemIconImage && ItemData.ItemIcon)
	{
		UE_LOG(LogTemp, Warning, TEXT("IconSuccess"));
		ItemIconImage->SetBrushFromTexture(ItemData.ItemIcon);
	}

	if (ItemCountText)
	{
		UE_LOG(LogTemp, Warning, TEXT("CountText Success"));
		ItemCountText->SetText(FText::AsNumber(ItemData.ItemCount));
	}
}
