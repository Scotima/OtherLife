#include "Inventory/CMakeFoodWidget.h"
#include "Inventory/CFoodItemWidget.h"
#include "Blueprint/UserWidget.h"
#include "CMakeFoodWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "FarmCharacter/CCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/CGameInstance.h"


void UCMakeFoodWidget::NativeConstruct()
{

	Super::NativeConstruct();

	UGameInstance* GI = Cast<UCGameInstance>(GetGameInstance());

	if (GI)
	{
		SetInven();
	}


	
}

void UCMakeFoodWidget::ToogleInventory()
{
	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
	{
		CanvasSlot->SetZOrder(10);
	}

	
	
}

void UCMakeFoodWidget::SetZorder()
{

	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
	{
		CanvasSlot->SetZOrder(-1);
	}
}

void UCMakeFoodWidget::GoToInventory(int32 a)
{
	ACCharacter* character = Cast<ACCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCGameInstance* GI = Cast<UCGameInstance>(GetGameInstance());


	if (GI)
	{
		if (character)
		{
			const TArray<FItemStruct>& FoodData = GI->GetFoodData();
			character->PickupItem(FoodData[a]);
		}
	}
	

	
}

void UCMakeFoodWidget::SetInven()
{

	UCGameInstance* GI = Cast<UCGameInstance>(GetGameInstance());

	if (!GI)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance not found"));
		return;
	}
	
	const TArray<FItemStruct> FoodData = GI->GetFoodData();


	for (int i = 0; i < FoodData.Num(); i++)
	{
		if (FoodItemArray.IsValidIndex(i))
		{
			FoodItemArray[i]->SetItemData(FoodData[i]);
		}
	}


	if (FoodItemArray.Num() < FoodData.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Food item array size is not enough"));
		return;
	}
	



}
