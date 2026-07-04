#include "../Public/EntranceMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UEntranceMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartChallengeButton)
	{
		StartChallengeButton->OnClicked.AddDynamic(this, &UEntranceMenu::OnStartChallengeClicked);
	}
}

void UEntranceMenu::OnStartChallengeClicked()
{
	UGameplayStatics::OpenLevel(this, FName("GameplayScene"));
}