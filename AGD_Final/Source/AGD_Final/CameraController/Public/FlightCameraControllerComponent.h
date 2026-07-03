#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "FlightCameraControllerComponent.generated.h"

class USpringArmComponent;
class ACharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AGD_FINAL_API UFlightCameraControllerComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	UFlightCameraControllerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Flight Camera")
	float SlowCameraDistance = 400.0f;

	UPROPERTY(EditAnywhere, Category = "Flight Camera")
	float FastCameraDistance = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Flight Camera")
	float SlowFOV = 90.0f;

	UPROPERTY(EditAnywhere, Category = "Flight Camera")
	float FastFOV = 110.0f;

	UPROPERTY(EditAnywhere, Category = "Flight Camera")
	float CameraInterpolationSpeed = .5f;

private:
	USpringArmComponent* ParentSpringArm;
	ACharacter* OwnerCharacter;

	float CurrentSpeedAlpha = 0.0f;
};