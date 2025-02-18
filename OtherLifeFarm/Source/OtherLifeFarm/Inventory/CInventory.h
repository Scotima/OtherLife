
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CItemWidget.h"
#include "CInventory.generated.h"


UCLASS()
class OTHERLIFEFARM_API UCInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

	void SetInventoryOpen(bool a) { bIsInventoryOpen = a; }

	bool GetInventoryOpen() { return bIsInventoryOpen; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<UCItemWidget*> Itemarray;

	void SetInven(int32 index, FItemStruct data)
	{
		
		Itemarray[index]->SetItemData(data);
	}
protected:
	virtual void NativeConstruct() override;


private:
	bool bIsInventoryOpen;
	
};
