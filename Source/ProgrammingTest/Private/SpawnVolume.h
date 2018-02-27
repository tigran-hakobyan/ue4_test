// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns placeholder for pickups */
	FORCEINLINE class UBoxComponent* GetPlaceholder() const { return Placeholder; }

	/** Returns a random point within the placeholder */
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInPlaceholder();

	/** Enable or disable the spawning ability */
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetSpawnActive(bool bShouldSpawn);

	FTimerHandle SpawnTimer;

	/** The minimum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	/** The maximum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;

protected:
	/** The pickup to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class APickup> PickupToSpawn;

private:
	/** Placeholder for pickups */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Placeholder;
	
	/** Spawns the pickup */
	void SpawnPickup();

	/** The current spawn delay */
	float CurrentSpawnDelay;
};
