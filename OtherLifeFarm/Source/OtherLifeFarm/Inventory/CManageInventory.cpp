#include "Inventory/CManageInventory.h"
#include "FItemStruct.h"
#include "CItemWidget.h"
#include "Components/PanelWidget.h"

void UCManageInventory::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCManageInventory::AddItem(FItemStruct NewItem)
{
	UE_LOG(LogTemp, Warning, TEXT("AddItem Success"));
	InventoryItems.Add(NewItem);
	UpdateUI();
}

void UCManageInventory::RemoveItem(int32 Index)
{
	if (InventoryItems.IsValidIndex(Index))
	{
		InventoryItems.RemoveAt(Index);
		UpdateUI();
	}
}

void UCManageInventory::UpdateUI()
{
	UE_LOG(LogTemp, Warning, TEXT("UpdateUI Success"));

	for (UWidget* Widget : ItemWidgetList)
	{
		Widget->RemoveFromParent();
	}
	ItemWidgetList.Empty();

	for (const FItemStruct& Item : InventoryItems)
	{
		UCItemWidget* NewItemWidget = CreateWidget<UCItemWidget>(this, ItemWidgetClass);

		if (NewItemWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("NewItemWidget is not null"));
			NewItemWidget->SetItemData(Item);
			InventoryPanel->AddChild(NewItemWidget);
			ItemWidgetList.Add(NewItemWidget);
		}
	}
}
