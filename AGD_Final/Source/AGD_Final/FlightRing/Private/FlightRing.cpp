#include "../Public/FlightRing.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "AGD_Final/GameMode/Public/ATimeTrialGameMode.h"

AFlightRing::AFlightRing()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

	BoxCollider->InitBoxExtent(FVector(50.0f, 300.0f, 300.0f));
	BoxCollider->SetCollisionProfileName(TEXT("Trigger"));
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
			TimeTrialGM->AddRingScore(RingBaseScore, TimePenaltyRate);
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