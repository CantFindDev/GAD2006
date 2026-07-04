#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayHUD.generated.h" // MUST be the last include

class UTextBlock;

UCLASS()
class AGD_FINAL_API UGameplayHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* GameplayHUDScoreAnimation;

	UFUNCTION()
	void UpdateScoreDisplay(int32 NewScore);
};