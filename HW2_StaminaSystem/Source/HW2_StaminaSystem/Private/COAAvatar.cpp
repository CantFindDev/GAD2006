// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"

#include "GameFramework/CharacterMovementComponent.h"

ACOAAvatar::ACOAAvatar() :
RunSpeed(300.0f),
MaxStamina(100.0f),
StaminaGainRate(10),
StaminaDrainRate(15),
bStaminaDrained(false),
bRunning(false)
{
	PrimaryActorTick.bCanEverTick = true;

	Stamina = MaxStamina;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm->TargetArmLength = 300.0f;
	mSpringArm->SetupAttachment(RootComponent);

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mCamera->SetupAttachment(mSpringArm,USpringArmComponent::SocketName);

	mCamera->bUsePawnControlRotation = false;
	mSpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
}

void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn",this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACOAAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACOAAvatar::MoveRight);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&ACOAAvatar::RunReleased);
}

void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bIsMoving = GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking;

	if (bRunning && bIsMoving && !bStaminaDrained)
	{
		Stamina -= StaminaDrainRate * DeltaTime;

		if (Stamina <= 0.0f)
		{
			Stamina = 0.0f;
			bStaminaDrained = true;
			RunReleased();
		}
		return;
	}

	if (Stamina < MaxStamina)
	{
		Stamina += StaminaGainRate * DeltaTime;

		if (Stamina >= MaxStamina)
		{
			Stamina = MaxStamina;
			bStaminaDrained = false;
		}
	}
}


void ACOAAvatar::RunPressed()
{
	if (bStaminaDrained)
	{
		RunReleased();
		return;
	}
	bRunning = true;
	UpdateMovmentParams();
}

void ACOAAvatar::RunReleased()
{
	if (!bRunning) return;
	bRunning = false;
	UpdateMovmentParams();
}

void ACOAAvatar::UpdateMovmentParams()
{
	GetCharacterMovement()->MaxWalkSpeed = bRunning ? RunSpeed : WalkSpeed;
}

void ACOAAvatar::MoveForward(float value)
{
	AddMovementInput(GetMovmentDirectionBasedOnAxis(EAxis::X),value);
}

void ACOAAvatar::MoveRight(float value)
{
	AddMovementInput(GetMovmentDirectionBasedOnAxis(EAxis::Y),value);
}

FVector ACOAAvatar::GetMovmentDirectionBasedOnAxis(EAxis::Type dir)
{
	return FRotationMatrix(GetYaw()).GetUnitAxis(dir);
}

FRotator ACOAAvatar::GetYaw()
{
	FRotator rotation = GetController()->GetControlRotation();
	FRotator yawRotation(0.0f,rotation.Yaw,0.0f);
	return yawRotation;
}
