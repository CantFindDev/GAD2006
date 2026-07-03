#include "../Public/FlightCameraControllerComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UFlightCameraControllerComponent::UFlightCameraControllerComponent(): ParentSpringArm(nullptr), OwnerCharacter(nullptr)
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UFlightCameraControllerComponent::BeginPlay()
{
    Super::BeginPlay();

    ParentSpringArm = Cast<USpringArmComponent>(GetAttachParent());
    OwnerCharacter = Cast<ACharacter>(GetOwner());

    if (ParentSpringArm)
    {
        ParentSpringArm->bEnableCameraLag = true;
        ParentSpringArm->bEnableCameraRotationLag = true;
        ParentSpringArm->CameraLagSpeed = CameraLagSpeed;
        ParentSpringArm->CameraRotationLagSpeed = RotationLagSpeed;
        ParentSpringArm->CameraLagMaxDistance = 200.0f;

        ParentSpringArm->bUsePawnControlRotation = true;
    }
}

void UFlightCameraControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!OwnerCharacter || !OwnerCharacter->GetCharacterMovement() || !ParentSpringArm)
    {
        return;
    }

    float CurrentVelocity = OwnerCharacter->GetVelocity().Size();
    float MaxVelocity = OwnerCharacter->GetCharacterMovement()->MaxFlySpeed;

    float TargetSpeedAlpha = (MaxVelocity > 0.0f) ? FMath::Clamp(CurrentVelocity / MaxVelocity, 0.0f, 1.0f) : 0.0f;

    CurrentSpeedAlpha = FMath::FInterpTo(CurrentSpeedAlpha, TargetSpeedAlpha, DeltaTime, CameraInterpolationSpeed);

    float TargetFOV = FMath::Lerp(SlowFOV, FastFOV, CurrentSpeedAlpha);
    SetFieldOfView(TargetFOV);

    float TargetArmLength = FMath::Lerp(SlowCameraDistance, FastCameraDistance, CurrentSpeedAlpha);
    ParentSpringArm->TargetArmLength = TargetArmLength;

    float CurrentPitch = OwnerCharacter->GetActorRotation().Pitch;

    float DiveAlpha = FMath::Clamp(FMath::GetMappedRangeValueClamped(FVector2D(0.0f, -60.0f), FVector2D(0.0f, 1.0f), CurrentPitch), 0.0f, 1.0f);

    FVector TargetOffset = FMath::Lerp(StandardOffset, DiveOffset, DiveAlpha);
    ParentSpringArm->SocketOffset = FMath::VInterpTo(ParentSpringArm->SocketOffset, TargetOffset, DeltaTime, CameraInterpolationSpeed);
}