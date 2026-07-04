#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndUI.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class AGD_FINAL_API UEndUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateFinalScore(int32 FinalScore, float FinalTime);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	UButton* ContinueButton;

	UFUNCTION()
	void OnContinueClicked();
};