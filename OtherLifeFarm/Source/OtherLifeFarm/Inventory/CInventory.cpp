

#include "Inventory/CInventory.h"
#include "CInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "CItemWidget.h"
#include "Components/CanvasPanelSlot.h"

void UCInventory::ToggleInventory()
{
	
    SetZorder();
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

void UCInventory::SetZorder()
{

    if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
    {
        CanvasSlot->SetZOrder(2);
    }
}

void UCInventory::SetItemDataCount(int32 a, UPARAM(ref)FItemStruct& item)
{
    if (Data.IsValidIndex(a))
    {
        Data[a] = item;

        SetInven(a);
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
