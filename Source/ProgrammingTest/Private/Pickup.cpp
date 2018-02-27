// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsActive = true;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/** Return the active state */
bool APickup::IsActive()
{
	return bIsActive;
}

/** Return the active state */
void APickup::SetActive(bool NewActiveState)
{
	bIsActive = NewActiveState;
}

void APickup::WasCollected_Implementation()
{
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("Item collected: %S"), *PickupDebugString);
}