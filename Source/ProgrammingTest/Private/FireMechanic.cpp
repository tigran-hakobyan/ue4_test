// Fill out your copyright notice in the Description page of Project Settings.

#include "FireMechanic.h"

#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/World.h"


#include "ProgrammingTestCharacter.h"

// Sets default values for this component's properties
UFireMechanic::UFireMechanic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	WeaponConfig.WeaponRange = 1000.0f;
	WeaponConfig.WeaponSpreadAmount = 10;
	WeaponConfig.WeaponSpreadAngle = 15.0f;
	WeaponConfig.HitStrength = 1000000.0f;

	// ...
}


// Called when the game starts
void UFireMechanic::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFireMechanic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/** Generic method should be called to handle different type of weapon */
void UFireMechanic::Fire(FVector StartTrace, FVector ForwardVector)
{
	if (EWeaponProjectile::EBullet == ProjectileType)
	{
		InstantBulletFire(StartTrace, ForwardVector);
	}
	if (EWeaponProjectile::ESpread == ProjectileType)
	{
		for (int32 i = 0; i < WeaponConfig.WeaponSpreadAmount; ++i)
		{
			InstantBulletFire(StartTrace, ForwardVector);
		}
	}
	if (EWeaponProjectile::EProjectile == ProjectileType)
	{
		AProgrammingTestCharacter* owner = Cast<AProgrammingTestCharacter>(GetOwner());
		if (owner != NULL)
		{
			owner->FireProjectile();
		}
	}
}

/** Bullet instant fire dedicated method */
void UFireMechanic::InstantBulletFire(FVector StartTrace, FVector ForwardVector)
{
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float CurrentSpread = WeaponConfig.WeaponSpreadAmount;
	const float SpreadCone = FMath::DegreesToRadians(WeaponConfig.WeaponSpreadAngle * 0.5);
	const FVector ShootDir = WeaponRandomStream.VRandCone(ForwardVector, SpreadCone, SpreadCone);
	const FVector EndTrace = StartTrace + ShootDir * WeaponConfig.WeaponRange;
	const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	ProcessInstantHit(Impact, StartTrace, ShootDir, RandomSeed, CurrentSpread);
}

/** Raycast performing function for hit detection */
FHitResult UFireMechanic::WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo) const
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams;
	TraceParams.TraceTag = WeaponFireTag;
	TraceParams.bTraceComplex = true;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	AProgrammingTestCharacter* owner = Cast<AProgrammingTestCharacter>(GetOwner());
	if (owner != NULL)
	{
		TraceParams.AddIgnoredActor(owner);
	}	
	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, ECC_Visibility, TraceParams);
	return Hit;
}

/** Hit processing method */
void UFireMechanic::ProcessInstantHit(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDir, int32 RandomSeed, float ReticleSpread)
{
	//DrawDebugLine(GetWorld(), Origin, EndPoint, FColor(255, 0, 0), true);
	AActor* actor = Impact.GetActor();
	if (actor != NULL)
	{
		const FVector EndPoint = Impact.ImpactPoint;

		UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(actor->GetRootComponent());

		//If the static mesh is valid apply the given impulse
		if (StaticMeshComponent && StaticMeshComponent->Mobility == EComponentMobility::Movable)
		{
			DrawDebugPoint(GetWorld(), EndPoint, 5.0f, FColor(255, 0, 255), true, 1.0f);
			FVector ForceToAdd = EndPoint - Origin;
			if (ForceToAdd.Normalize())
			{
				ForceToAdd *= WeaponConfig.HitStrength / Impact.Distance;
				StaticMeshComponent->AddImpulse(ForceToAdd*StaticMeshComponent->GetMass());
			}
		}
		else
		{
			DrawDebugPoint(GetWorld(), EndPoint, 5.0f, FColor(255, 0, 255), true);
		}
	}
}

