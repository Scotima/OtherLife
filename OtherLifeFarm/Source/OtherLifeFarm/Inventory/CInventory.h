
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FItemStruct.h"
#include "CInventory.generated.h"

class UCItemWidget;

UCLASS()
class OTHERLIFEFARM_API UCInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

	UFUNCTION(BlueprintCallable)
	void SetZorder();

	UFUNCTION(BlueprintCallable)
	void SetItemDataCount(int32 a, UPARAM(ref)FItemStruct& item);

	UFUNCTION(BlueprintCallable)
	void LoadInventory();

	UFUNCTION(BlueprintCallable)
	void LoadSaveInventory();

public:

	void SetInventoryOpen(bool a) { bIsInventoryOpen = a; }

	bool GetInventoryOpen() { return bIsInventoryOpen; }

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<UCItemWidget*> Itemarray;
	
	//UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	//TArray<FItemStruct> Data;
	
public:
	//void SetData(const FItemStruct& a) { Data.Add(a); }
	void SetInven(int32 a);

	
	





protected:
	virtual void NativeConstruct() override;


private:
	bool bIsInventoryOpen;
	
};
