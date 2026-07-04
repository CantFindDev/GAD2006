#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntranceMenu.generated.h"

class UButton;

UCLASS()
class AGD_FINAL_API UEntranceMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* StartChallengeButton;

	UFUNCTION()
	void OnStartChallengeClicked();
};