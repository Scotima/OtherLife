#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FItemStruct.h"
#include "CItemWidget.generated.h"


UCLASS()
class OTHERLIFEFARM_API UCItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetItemData(const FItemStruct& ItemData);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIconImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemCountText;
};
