#include "DialogueWidget/CDialogueWidget.h"
#include "Components/TextBlock.h"

void UCDialogueWidget::SetDialogue(const FString& Text)
{

	if (DialogueText)
	{
		DialogueText->SetText(FText::FromString(Text));
	}

}
