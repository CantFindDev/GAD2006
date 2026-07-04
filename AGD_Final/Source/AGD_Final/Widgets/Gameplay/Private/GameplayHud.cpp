#include "../Public/GameplayHUD.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "AGD_Final/GameMode/Public/ATimeTrialGameMode.h"

void UGameplayHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString("0"));
	}

	ATimeTrialGameMode* GameMode = Cast<ATimeTrialGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->OnScoreChanged.AddDynamic(this, &UGameplayHUD::UpdateScoreDisplay);
	}
}

void UGameplayHUD::UpdateScoreDisplay(int32 NewScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(NewScore));
	}

	if (GameplayHUDScoreAnimation)
	{
		PlayAnimation(GameplayHUDScoreAnimation);
	}
}