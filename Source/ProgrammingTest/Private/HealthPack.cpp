// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPack.h"


/** Sets default values */
AHealthPack::AHealthPack()
{
	GetMesh()->SetSimulatePhysics(true);

	HealthAmount = 20.0f;
}

void AHealthPack::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();
	Destroy();
}

float AHealthPack::GetHealth()
{
	return HealthAmount;
}
