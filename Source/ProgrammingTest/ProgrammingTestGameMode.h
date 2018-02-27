// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ProgrammingTestGameMode.generated.h"

UENUM(BlueprintType)
enum class ETestGamePlayState : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

template<typename T>
static FString EnumToString(const FString& enumName, const T value)
{
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName);
	return *(pEnum ? pEnum->GetNameStringByIndex(static_cast<uint8>(value)) : "null");
}

UCLASS(minimalapi)
class AProgrammingTestGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AProgrammingTestGameMode();

	virtual void Tick(float DeltaTime) override;

	/** Returns the health needed to win the game */
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthToWin() const;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Health")
	ETestGamePlayState GetCurrentState() const;

	void SetCurrentState(ETestGamePlayState NewState);

protected:
	/** The rate at which the character loses health */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", Meta = (BlueprintProtected = "true"))
	float DecayRate;

	/** The Health needed to win the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", Meta = (BlueprintProtected = "true"))
	float HealthToWin;

private:
	/** The current game state */
	ETestGamePlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	void HandleNewState(ETestGamePlayState NewState);

	void StopPlaying();
};



