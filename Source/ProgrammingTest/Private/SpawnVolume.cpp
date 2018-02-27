// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Placeholder = CreateDefaultSubobject<UBoxComponent>(TEXT("Placeholder"));
	RootComponent = Placeholder;
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/** Returns a random point within the placeholder */
FVector ASpawnVolume::GetRandomPointInPlaceholder()
{
	FVector PlaceholderOrigin = Placeholder->Bounds.Origin;
	FVector PlaceholderExtent = Placeholder->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(PlaceholderOrigin, PlaceholderExtent);
}

void ASpawnVolume::SetSpawnActive(bool bShouldSpawn)
{
	if (bShouldSpawn)
	{
		CurrentSpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, CurrentSpawnDelay, false);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

/** Spawns the pickup */
void ASpawnVolume::SpawnPickup()
{
	if (PickupToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			FVector SpawnLocation = GetRandomPointInPlaceholder();
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(PickupToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			CurrentSpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, CurrentSpawnDelay, false);
		}
	}
}

