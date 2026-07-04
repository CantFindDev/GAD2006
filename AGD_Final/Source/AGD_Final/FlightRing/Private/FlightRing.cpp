#include "../Public/FlightRing.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "AGD_Final/GameMode/Public/ATimeTrialGameMode.h"
#include "NiagaraComponent.h"
#include "Curves/CurveLinearColor.h"

AFlightRing::AFlightRing()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

	BoxCollider->InitBoxExtent(FVector(50.0f, 300.0f, 300.0f));
	BoxCollider->SetCollisionProfileName(TEXT("Trigger"));

	RingEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RingEffect"));
	RingEffect->SetupAttachment(RootComponent);
}

void AFlightRing::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (RingEffect)
	{
		FLinearColor LeftColor;
		FLinearColor RightColor;

		switch (RingType)
		{
		case ERingType::Start:
			LeftColor = StartColorLeft;
			RightColor = StartColorRight;
			break;

		case ERingType::End:
			LeftColor = EndColorLeft;
			RightColor = EndColorRight;
			break;

		case ERingType::Normal:
			LeftColor = NormalColorLeft;
			RightColor = NormalColorRight;
			break;
		}

		RingEffect->SetVariableLinearColor(FName("RimColorLeft"), LeftColor);
		RingEffect->SetVariableLinearColor(FName("RimColorRight"), RightColor);
		RingEffect->SetVariableFloat(FName("LerpFactor"), LerpFactor);
	}
}

void AFlightRing::BeginPlay()
{
	Super::BeginPlay();

	if (BoxCollider)
	{
		BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AFlightRing::OnRingOverlap);
	}
}

void AFlightRing::OnRingOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor->IsA(ACharacter::StaticClass()))
	{
		if (ATimeTrialGameMode* TimeTrialGM = Cast<ATimeTrialGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			switch (RingType)
			{
			case ERingType::Start:
				TimeTrialGM->StartRace();
				break;

			case ERingType::Normal:
				TimeTrialGM->AddRingScore(RingBaseScore, TimePenaltyRate);
				break;

			case ERingType::End:
				TimeTrialGM->AddRingScore(RingBaseScore, TimePenaltyRate);
				TimeTrialGM->EndRace();
				break;
			}
		}

		if (SuccessSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SuccessSound, GetActorLocation());
		}

		if (SuccessParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SuccessParticles, GetActorTransform());
		}

		Destroy();
	}
}