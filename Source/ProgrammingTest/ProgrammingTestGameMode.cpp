// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ProgrammingTestGameMode.h"
#include "ProgrammingTestHUD.h"
#include "ProgrammingTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Private/SpawnVolume.h"

AProgrammingTestGameMode::AProgrammingTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProgrammingTestHUD::StaticClass();

	DecayRate = 0.1f;
	HealthToWin = 120.0;
}

void AProgrammingTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	//find all spawn volume actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentState(ETestGamePlayState::EPlaying);
}

void AProgrammingTestGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AProgrammingTestCharacter* MyCharacter = Cast<AProgrammingTestCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		if (MyCharacter->GetCurrentHealth() > GetHealthToWin())
		{
			SetCurrentState(ETestGamePlayState::EWon);
		}
		else if (MyCharacter->GetCurrentHealth() > 0)
		{
			MyCharacter->UpdateHealth(-DeltaTime * DecayRate*(MyCharacter->GetInitialHealth()));
		}
		else
		{
			SetCurrentState(ETestGamePlayState::EGameOver);
		}
	}
}

float AProgrammingTestGameMode::GetHealthToWin() const
{
	return HealthToWin;
}

ETestGamePlayState AProgrammingTestGameMode::GetCurrentState() const
{
	return CurrentState;
}

void AProgrammingTestGameMode::SetCurrentState(ETestGamePlayState NewState)
{
	CurrentState = NewState;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, EnumToString("ETestGamePlayState", CurrentState));
	}
	HandleNewState(NewState);
}

void AProgrammingTestGameMode::HandleNewState(ETestGamePlayState NewState)
{
	switch (NewState)
	{
		case ETestGamePlayState::EPlaying:
		{
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->SetSpawnActive(true);
			}
		}
		break;
		case ETestGamePlayState::EWon:
		{
			StopPlaying();
		}
		break;
		case ETestGamePlayState::EGameOver:
		{
			StopPlaying();
		}
		break;
		case ETestGamePlayState::EUnknown:
		{
			//nothing to do
		}
		break;
	}
}

void AProgrammingTestGameMode::StopPlaying()
{
	for (ASpawnVolume* Volume : SpawnVolumeActors)
	{
		Volume->SetSpawnActive(false);
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->SetCinematicMode(true, false, false, true, true);
	}
}