

#include "Inventory/CInventory.h"
#include "CInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "CItemWidget.h"

void UCInventory::ToggleInventory()
{
	

    bIsInventoryOpen = !bIsInventoryOpen;

    if (bIsInventoryOpen)
    {
        this->SetVisibility(ESlateVisibility::Visible);
        //UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetOwningPlayer());
    }
    else
    {
        this->SetVisibility(ESlateVisibility::Hidden);
        //UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetOwningPlayer());
    }
}

void UCInventory::SetInven(int32 a)
{
    
    
    Itemarray[a]->SetItemData(Data[a]);
    
}

void UCInventory::NativeConstruct()
{
	Super::NativeConstruct();
	bIsInventoryOpen = false;
   // Itemarray.SetNum(1);
    //Itemarray.Add(CreateWidget<>)
}
