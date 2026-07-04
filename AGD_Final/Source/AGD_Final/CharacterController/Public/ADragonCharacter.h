#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ADragonCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class AGD_FINAL_API ADragonCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADragonCharacter();
    virtual void Tick(float DeltaTime) override;

    virtual void PostInitProperties() override;

    UFUNCTION(BlueprintCallable, Category = "Flight")
    void ForceBrake();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dragon Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dragon Input")
    UInputAction* MoveHorizontalAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dragon Input")
    UInputAction* MoveUpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dragon Input")
    UInputAction* DiveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dragon Input")
    UInputAction* HandBrakeAction;

    void MoveHorizontal(const FInputActionValue& Value);
    void MoveUp(const FInputActionValue& Value);
    void StartDive(const FInputActionValue& Value);
    void StopDive(const FInputActionValue& Value);
    void ToggleHandBrake(const FInputActionValue& Value);

    void HandleForwardMovement(float DeltaTime);
    void HandleMeshRotation(float DeltaTime);

    UPROPERTY(BlueprintReadOnly, Category = "Dragon Flight|State")
    bool bIsBraking = false;

    UPROPERTY(BlueprintReadOnly, Category = "Dragon Flight|State")
    bool bIsDiving = false;

    UPROPERTY(BlueprintReadOnly, Category = "Dragon Flight|State")
    float CurrentForwardInput = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Dragon Flight|State")
    float CurrentTurnInput = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Dragon Flight|State")
    float CurrentUpInput = 0.0f;

    UPROPERTY()
    FRotator BaseMeshRotation;

    UPROPERTY(EditAnywhere, Category = "Dragon Flight")
    float HoverSpeed = 1000.f;

    UPROPERTY(EditAnywhere, Category = "Dragon Flight")
    float DiveGravityMultiplier = 4.0f;

    UPROPERTY(EditAnywhere, Category = "Dragon Flight")
    float AccelerationSpeed = 2.0f;

    UPROPERTY(EditAnywhere, Category = "Dragon Flight")
    float DecelerationSpeed = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Dragon Flight")
    float TurnSpeed = 25.0f;

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Dragon Flight|Animation")
    float MaxBankAngle = 60.0f;

    UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Dragon Flight|Animation")
    float MaxPitchUpAngle = 25.0f;

    UPROPERTY(EditAnywhere, Category = "Dragon Flight|Animation")
    float MaxDivePitchAngle = -45.0f;

    UPROPERTY(EditAnywhere, Category = "Dragon Flight|Animation")
    float BrakingPitchAngle = 15.0f;

    UPROPERTY(EditAnywhere, Category = "Dragon Flight|Animation")
    float RotationInterpSpeed = 5.0f;
};