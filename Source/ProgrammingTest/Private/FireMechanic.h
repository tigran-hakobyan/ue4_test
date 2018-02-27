// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireMechanic.generated.h"


UENUM(BlueprintType)
namespace EWeaponProjectile
{
	enum ProjectileType
	{
		EBullet			UMETA(DisplayName = "Bullet"),
		ESpread			UMETA(DisplayName = "Spread"),
		EProjectile		UMETA(DisplayName = "Projectile")
	};
}

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()


		UPROPERTY(EditDefaultsOnly, Category = Ammo)
		float WeaponRange;

		UPROPERTY(EditDefaultsOnly, Category = Ammo)
		int32 WeaponSpreadAmount;

		UPROPERTY(EditDefaultsOnly, Category = Ammo)
		float WeaponSpreadAngle;

		UPROPERTY(EditDefaultsOnly, Category = Ammo)
		float HitStrength;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UFireMechanic : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireMechanic();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Generic method should be called to handle different type of weapon */
	UFUNCTION()
	void Fire(FVector StartTrace, FVector ForwardVector);

	/** Bullet instant fire dedicated method */
	UFUNCTION()
	void InstantBulletFire(FVector StartTrace, FVector ForwardVector);

public:
	/** Weapon configuration property */
	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponData WeaponConfig;

	/** The current projectile type */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Config)
	TEnumAsByte<EWeaponProjectile::ProjectileType> ProjectileType;

protected:
	/** Raycast performing function for hit detection */
	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo) const;

	/** Hit processing method */
	void ProcessInstantHit(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDir, int32 RandomSeed, float ReticleSpread);
	
};
