#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "FlightRing.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USoundBase;
class UParticleSystem;

UCLASS()
class AGD_FINAL_API AFlightRing : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlightRing();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings")
	float RingBaseScore = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings")
	float TimePenaltyRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* SuccessSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* SuccessParticles;
};