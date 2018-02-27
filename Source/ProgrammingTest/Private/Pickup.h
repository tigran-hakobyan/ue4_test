// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class PROGRAMMINGTEST_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Return the mesh for the pickup */
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return PickupMesh; }

	/** Return the active state */
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	/** Set the active state */
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewActiveState);

	/** Needs to be called when collected */
	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();

	virtual void WasCollected_Implementation();

protected:
	/** True when active */
	bool bIsActive;

private:
	/** Static mesh to represent the pickup */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;
	
	
};
