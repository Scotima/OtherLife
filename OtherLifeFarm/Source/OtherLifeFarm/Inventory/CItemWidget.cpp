#include "Inventory/CItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"

void UCItemWidget::NativeConstruct()
{
    Super::NativeConstruct(); // 부모 클래스 초기화

    if (!ItemNameText)
    {
        UE_LOG(LogTemp, Error, TEXT("ItemNameText is nullptr!"));
    }

    if (!ItemIconImage)
    {
        UE_LOG(LogTemp, Error, TEXT("ItemIconImage is nullptr!"));
    }
}

void UCItemWidget::SetItemData(const FItemStruct& ItemData)
{
    UE_LOG(LogTemp, Warning, TEXT("SetItemData Succeess"));

    UE_LOG(LogTemp, Log, TEXT("SetItemData called - Name: %s, Count: %d"),
        *ItemData.ItemName, ItemData.ItemCount);


    if (!ItemNameText || !ItemIconImage || !ItemCountText)
    {
        UE_LOG(LogTemp, Error, TEXT("One or more widget bindings are NULL in SetItemData!"));
    }

    if (ItemNameText)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemNameText before set: %s"), *ItemNameText->GetText().ToString());
        ItemNameText->SetText(FText::FromString(ItemData.ItemName));
        UE_LOG(LogTemp, Warning, TEXT("ItemNameText after set: %s"), *ItemNameText->GetText().ToString());
    }
    
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ItemNameText is null"));
    }

    if (ItemIconImage && ItemData.ItemIcon)
    {
        UE_LOG(LogTemp, Warning, TEXT("IconSuccess"));
       
        ItemIconImage->SetBrushFromTexture(ItemData.ItemIcon);
        ItemIconImage->InvalidateLayoutAndVolatility();
        ItemIconImage->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        if (!ItemIconImage)
        {
            UE_LOG(LogTemp, Error, TEXT("ItemIconImage is null"));
        }
        if (!ItemData.ItemIcon)
        {
            UE_LOG(LogTemp, Error, TEXT("ItemData.ItemIcon is null"));
        }
    }

    if (ItemCountText)
    {
        UE_LOG(LogTemp, Warning, TEXT("CountText Success"));
        UE_LOG(LogTemp, Warning, TEXT("ItemCountText before set: %s"), *ItemCountText->GetText().ToString());
        ItemCountText->SetText(FText::AsNumber(ItemData.ItemCount));

        UE_LOG(LogTemp, Warning, TEXT("ItemCountText after set: %s"), *ItemCountText->GetText().ToString());
        ItemCountText->InvalidateLayoutAndVolatility();
        ItemCountText->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ItemCountText is null"));
    }

    this->SetVisibility(ESlateVisibility::Visible);
    SynchronizeProperties();
   
}

void UCItemWidget::AddChildToPanel(UWidget* Widget)
{
    if (ItemPanel && Widget)
    {
        ItemPanel->AddChild(Widget);
        UE_LOG(LogTemp, Warning, TEXT("NewItemWidget added to InventoryPanel!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ItemPanel or Widget is null"));
    }
}