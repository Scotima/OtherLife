

#include "Inventory/CInventory.h"
#include "CInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "CItemWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "GameInstance/CGameInstance.h"

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
    UCGameInstance* mygameinstance = Cast<UCGameInstance>(GetGameInstance());

    if (mygameinstance)
    {
        if (mygameinstance->Data.IsValidIndex(a))
        {
            mygameinstance->Data[a] = item;
            SetInven(a);
        }
    }


   
}

void UCInventory::LoadInventory()
{
    UCGameInstance* mygameinstance = Cast<UCGameInstance>(GetGameInstance());

    if (mygameinstance)
    {
        int DataNum = mygameinstance->Data.Num();
        for (int i = 0; i < DataNum; i++)
        {
            Itemarray[i]->SetItemData(mygameinstance->Data[i]);
        }
    }
}

void UCInventory::SetInven(int32 a)
{
    UCGameInstance* mygameinstance = Cast<UCGameInstance>(GetGameInstance());
    
    if (mygameinstance)
    {
        for (int i = 0; i < mygameinstance->Data.Num(); i++)
        {
            Itemarray[i]->SetItemData(mygameinstance->Data[i]);

        }
    }
    
    
}

void UCInventory::NativeConstruct()
{
	Super::NativeConstruct();
	bIsInventoryOpen = false;
   // Itemarray.SetNum(1);
    //Itemarray.Add(CreateWidget<>)
}
