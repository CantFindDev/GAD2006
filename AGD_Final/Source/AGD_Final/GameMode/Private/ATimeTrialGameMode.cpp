#include "../Public/ATimeTrialGameMode.h"

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
	CurrentRaceTime = 0.0f;
	TotalScore = 0;
	bIsRaceActive = true;
}

void ATimeTrialGameMode::EndRace()
{
	bIsRaceActive = false;
}

void ATimeTrialGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartRace();
}

void ATimeTrialGameMode::AddRingScore(float RingBaseValue, float TimePenaltyRate)
{
	if (!bIsRaceActive) return;

	float CalculatedScore = RingBaseValue - (CurrentRaceTime * TimePenaltyRate);

	CalculatedScore = FMath::Max(10.0f, CalculatedScore);

	TotalScore += FMath::RoundToInt(CalculatedScore);

	OnScoreChanged.Broadcast(TotalScore);
}