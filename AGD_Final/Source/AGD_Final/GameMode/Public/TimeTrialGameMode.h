#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeTrialGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedSignature, int32, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreRaceStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreRaceEndSignature, int32, EndScore, float, EndTime);

UCLASS()
class AGD_FINAL_API ATimeTrialGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATimeTrialGameMode();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Time Trial")
	void StartRace();

	UFUNCTION(BlueprintCallable, Category = "Time Trial")
	void EndRace();

	UFUNCTION(BlueprintCallable, Category = "Time Trial")
	void AddRingScore(float RingBaseValue, float TimePenaltyRate);

	UPROPERTY(BlueprintAssignable, Category = "Time Trial Events")
	FOnScoreChangedSignature OnScoreChanged;

	UPROPERTY(BlueprintAssignable, Category = "Time Trial Events")
	FOnScoreRaceStartSignature OnGameStart;

	UPROPERTY(BlueprintAssignable, Category = "Time Trial Events")
	FOnScoreRaceEndSignature OnRaceEnd;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Time Trial")
	bool bIsRaceActive = false;

	UPROPERTY(BlueprintReadOnly, Category = "Time Trial")
	float CurrentRaceTime = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Time Trial")
	int32 TotalScore = 0;
};