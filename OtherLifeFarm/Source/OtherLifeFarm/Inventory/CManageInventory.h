
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FItemStruct.h"
#include "CManageInventory.generated.h"

UCLASS()
class OTHERLIFEFARM_API UCManageInventory : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void AddItem(FItemStruct NewItem);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	void UpdateUI();

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FItemStruct> InventoryItems;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UWidget*> ItemWidgetList;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* InventoryPanel; 

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<class UCItemWidget> ItemWidgetClass;

};
