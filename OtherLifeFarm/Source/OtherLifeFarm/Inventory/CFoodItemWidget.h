// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FItemStruct.h"
#include "CFoodItemWidget.generated.h"

class UTextBlock;
class UImage;
class UPanelWidget;

UCLASS()
class OTHERLIFEFARM_API UCFoodItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct();

	UFUNCTION(BlueprintCallable)
	void SetItemData(FItemStruct& FoodData);

	UFUNCTION(BlueprintCallable)
	void AddChildToPanel(UWidget* Widget);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FoodNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* FoodIconImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FoodNameCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* ItemPanel;

	
};
