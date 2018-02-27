// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPack.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGTEST_API AHealthPack : public APickup
{
	GENERATED_BODY()
	
public:
	/** Sets default values */
	AHealthPack();
	
	void WasCollected_Implementation() override;

	/** Returns the health amount */
	float GetHealth();

protected:
	/** Amount of health */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", Meta = (BlueprintProtected = "true"))
	float HealthAmount;
	
};
