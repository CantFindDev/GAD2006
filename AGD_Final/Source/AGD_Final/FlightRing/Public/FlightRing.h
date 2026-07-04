#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "FlightRing.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USoundBase;
class UParticleSystem;
class UNiagaraComponent;
class UCurveLinearColor;

UENUM(BlueprintType)
enum class ERingType : uint8
{
	Normal  UMETA(DisplayName = "Normal Ring"),
	Start   UMETA(DisplayName = "Start Ring"),
	End     UMETA(DisplayName = "End Ring")
};

UCLASS()
class AGD_FINAL_API AFlightRing : public AActor
{
	GENERATED_BODY()

public:
	AFlightRing();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNiagaraComponent* RingEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings")
	ERingType RingType = ERingType::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings|Colors")
	FLinearColor NormalColorLeft = FLinearColor(1.0f, 1.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings|Colors")
	FLinearColor NormalColorRight = FLinearColor(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings|Colors")
	FLinearColor StartColorLeft = FLinearColor(0.0f, 1.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings|Colors")
	FLinearColor StartColorRight = FLinearColor(0.0f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings|Colors")
	FLinearColor EndColorLeft = FLinearColor(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings|Colors")
	FLinearColor EndColorRight = FLinearColor(0.1f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings|Colors")
	float LerpFactor = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings")
	float RingBaseScore = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Trial Settings")
	float TimePenaltyRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* SuccessSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* SuccessParticles;
};