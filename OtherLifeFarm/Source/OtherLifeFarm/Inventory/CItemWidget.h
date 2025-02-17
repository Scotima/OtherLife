#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FItemStruct.h"
#include "CItemWidget.generated.h"

class UTextBlock;
class UImage;
class UPanelWidget;
UCLASS()
class OTHERLIFEFARM_API UCItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct();
	UFUNCTION(BlueprintCallable)
	void SetItemData(const FItemStruct& ItemData);

	UFUNCTION(BlueprintCallable)
	void AddChildToPanel(UWidget* Widget);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemIconImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemCountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* ItemPanel;
};

