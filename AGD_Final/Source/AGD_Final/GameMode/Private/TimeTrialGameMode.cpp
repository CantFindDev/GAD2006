#include "../Public/TimeTrialGameMode.h"

ATimeTrialGameMode::ATimeTrialGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimeTrialGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsRaceActive)
	{
		CurrentRaceTime += DeltaSeconds;
	}
}

void ATimeTrialGameMode::StartRace()
{
	if (bIsRaceActive) return;

	CurrentRaceTime = 0.0f;
	TotalScore = 0;
	bIsRaceActive = true;
	OnGameStart.Broadcast();
}

void ATimeTrialGameMode::EndRace()
{
	if (!bIsRaceActive) return;

	bIsRaceActive = false;
	OnRaceEnd.Broadcast(TotalScore, CurrentRaceTime);
}

void ATimeTrialGameMode::AddRingScore(float RingBaseValue, float TimePenaltyRate)
{
	if (!bIsRaceActive) return;

	float CalculatedScore = RingBaseValue - (CurrentRaceTime * TimePenaltyRate);
	CalculatedScore = FMath::Max(10.0f, CalculatedScore);
	TotalScore += FMath::RoundToInt(CalculatedScore);

	OnScoreChanged.Broadcast(TotalScore);
}