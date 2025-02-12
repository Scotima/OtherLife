

#include "Inventory/CInventory.h"
#include "CInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UCInventory::ToggleInventory()
{
	

	if (bIsInventoryOpen)
	{
		this->SetVisibility(ESlateVisibility::Visible);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetOwningPlayer());
		
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetOwningPlayer());
	}
}

void UCInventory::NativeConstruct()
{
	Super::NativeConstruct();
	bIsInventoryOpen = false;
	
}
