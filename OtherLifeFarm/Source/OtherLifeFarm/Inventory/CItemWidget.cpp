#include "Inventory/CItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UCItemWidget::SetItemData(const FItemStruct& ItemData)
{
	if (ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(ItemData.ItemName));
	}

	if (ItemIconImage && ItemData.ItemIcon)
	{
		ItemIconImage->SetBrushFromTexture(ItemData.ItemIcon);
	}

	if (ItemCountText)
	{
		ItemCountText->SetText(FText::AsNumber(ItemData.ItemCount));
	}
}
