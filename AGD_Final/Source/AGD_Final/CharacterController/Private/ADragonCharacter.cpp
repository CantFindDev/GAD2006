#include "../Public/ADragonCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ADragonCharacter::ADragonCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->DefaultLandMovementMode = MOVE_Flying;
    GetCharacterMovement()->MovementMode = MOVE_Flying;

    GetCharacterMovement()->MaxFlySpeed = HoverSpeed;
    GetCharacterMovement()->BrakingDecelerationFlying = 500.f;
    GetCharacterMovement()->AirControl = 1.0f;

    bIsBraking = true;
    bIsDiving = false;
}

void ADragonCharacter::PostInitProperties()
{
    Super::PostInitProperties();
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxFlySpeed = HoverSpeed;
    }
}

void ADragonCharacter::ForceBrake()
{
    bIsBraking = true;

    if (bIsDiving)
    {
        bIsDiving = false;
        GetCharacterMovement()->SetMovementMode(MOVE_Flying);

        FVector CurrentVelocity = GetCharacterMovement()->Velocity;
        GetCharacterMovement()->Velocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0.0f);
        GetCharacterMovement()->GravityScale = 1.0f;
    }
}

void ADragonCharacter::BeginPlay()
{
    Super::BeginPlay();
    GetCharacterMovement()->SetMovementMode(MOVE_Flying);

    if (USkeletalMeshComponent* DragonMesh = GetMesh())
    {
        BaseMeshRotation = DragonMesh->GetRelativeRotation();
    }

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }
}

void ADragonCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleForwardMovement(DeltaTime);
    HandleMeshRotation(DeltaTime);

    CurrentTurnInput = 0.0f;
    CurrentUpInput = 0.0f;
}

void ADragonCharacter::HandleForwardMovement(float DeltaTime)
{
    float TargetForwardInput = bIsBraking ? 0.0f : 1.0f;
    float CurrentInterpSpeed = bIsBraking ? DecelerationSpeed : AccelerationSpeed;

    CurrentForwardInput = FMath::FInterpTo(CurrentForwardInput, TargetForwardInput, DeltaTime, CurrentInterpSpeed);

    if (CurrentForwardInput > 0.05f)
    {
        AddMovementInput(GetActorForwardVector(), CurrentForwardInput);
    }
}

void ADragonCharacter::HandleMeshRotation(float DeltaTime)
{
    USkeletalMeshComponent* DragonMesh = GetMesh();

    if (!DragonMesh) return;

    float TargetRollAngle = CurrentTurnInput * MaxBankAngle;
    float TargetPitchAngle = 0.0f;

    if (bIsBraking)
    {
        TargetPitchAngle = BrakingPitchAngle;
    }
    else if (bIsDiving)
    {
        TargetPitchAngle = MaxDivePitchAngle;
    }
    else if (CurrentUpInput != 0.0f)
    {
        TargetPitchAngle = CurrentUpInput * MaxPitchUpAngle;
    }

    FRotator FlightRotationOffset(TargetPitchAngle, 0.0f, TargetRollAngle);

    FQuat TargetQuat = FlightRotationOffset.Quaternion() * BaseMeshRotation.Quaternion();

    FQuat CurrentQuat = DragonMesh->GetRelativeRotation().Quaternion();
    FQuat NewQuat = FMath::QInterpTo(CurrentQuat, TargetQuat, DeltaTime, RotationInterpSpeed);

    DragonMesh->SetRelativeRotation(NewQuat.Rotator());
}

void ADragonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveHorizontalAction, ETriggerEvent::Triggered, this, &ADragonCharacter::MoveHorizontal);
        EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &ADragonCharacter::MoveUp);
        EnhancedInputComponent->BindAction(DiveAction, ETriggerEvent::Started, this, &ADragonCharacter::StartDive);
        EnhancedInputComponent->BindAction(DiveAction, ETriggerEvent::Completed, this, &ADragonCharacter::StopDive);
        EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Started, this, &ADragonCharacter::ToggleHandBrake);
    }
}

void ADragonCharacter::MoveHorizontal(const FInputActionValue& Value)
{
    float MovementValue = Value.Get<float>();
    if (MovementValue != 0.0f)
    {
        AddControllerYawInput(MovementValue * TurnSpeed * GetWorld()->GetDeltaSeconds());
        CurrentTurnInput = MovementValue;
    }
}

void ADragonCharacter::MoveUp(const FInputActionValue& Value)
{
    if (bIsBraking) return;

    float MovementValue = Value.Get<float>();
    if (MovementValue != 0.0f)
    {
        AddMovementInput(FVector::UpVector, MovementValue);
        CurrentUpInput = MovementValue;
    }
}

void ADragonCharacter::StartDive(const FInputActionValue& Value)
{
    if (bIsBraking) return;

    bIsDiving = true;
    GetCharacterMovement()->SetMovementMode(MOVE_Falling);
    GetCharacterMovement()->GravityScale = DiveGravityMultiplier;
}

void ADragonCharacter::StopDive(const FInputActionValue& Value)
{
    bIsDiving = false;
    GetCharacterMovement()->SetMovementMode(MOVE_Flying);

    FVector CurrentVelocity = GetCharacterMovement()->Velocity;
    GetCharacterMovement()->Velocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0.0f);

    GetCharacterMovement()->GravityScale = 1.0f;
}

void ADragonCharacter::ToggleHandBrake(const FInputActionValue& Value)
{
    bIsBraking = !bIsBraking;

    if (bIsBraking && bIsDiving)
    {
        bIsDiving = false;
        GetCharacterMovement()->SetMovementMode(MOVE_Flying);
        FVector CurrentVelocity = GetCharacterMovement()->Velocity;
        GetCharacterMovement()->Velocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0.0f);
        GetCharacterMovement()->GravityScale = 1.0f;
    }
}