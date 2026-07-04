#include "../Public/EndUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UEndUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UEndUI::OnContinueClicked);
	}

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetShowMouseCursor(true);

		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(this->TakeWidget());
		PC->SetInputMode(InputModeData);
	}
}

void UEndUI::UpdateFinalScore(int32 FinalScore, float FinalTime)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(FinalScore));
	}

	if (TimeText)
	{
		FNumberFormattingOptions Opts;
		Opts.SetMaximumFractionalDigits(2);
		Opts.SetMinimumFractionalDigits(2);
		TimeText->SetText(FText::AsNumber(FinalTime, &Opts));
	}
}

void UEndUI::OnContinueClicked()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->SetShowMouseCursor(false);

		FInputModeGameOnly InputModeData;
		PC->SetInputMode(InputModeData);
	}

	RemoveFromParent();
}