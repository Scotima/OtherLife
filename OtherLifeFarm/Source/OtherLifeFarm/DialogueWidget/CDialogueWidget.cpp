#include "DialogueWidget/CDialogueWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "FarmCharacter/CCharacter.h"
#include "PlayerController/CPlayerController.h"

void UCDialogueWidget::NativeConstruct()
{
	

}

void UCDialogueWidget::NativeDestruct()
{

	CancelDialogueWidgetWindow();
	//if (ACPlayerController* PC = Cast<ACPlayerController>(GetOwningPlayer()))
	//{
	//	
	//	/*PC->OnCancelPressed.RemoveDynamic(this, &UCDialogueWidget::CancelDialogueWidgetWindow);
	//	UE_LOG(LogTemp, Warning, TEXT("위젯 바인딩 시도됨"));
	//	PC->OnCancelPressed.AddDynamic(this, &UCDialogueWidget::CancelDialogueWidgetWindow);
	//	UE_LOG(LogTemp, Warning, TEXT("위젯 바인딩 완료"));*/
	//}
}

void UCDialogueWidget::CancelDialogueWidgetWindow()
{
	if (player)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is not nullptr"));
		player->EndDialogue();
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerNone"));
	}
}

void UCDialogueWidget::SetDialogue(const FString& Text)
{

	if (DialogueText)
	{
		DialogueText->SetText(FText::FromString(Text));
	}

}
