// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProgrammingTestHUD.generated.h"

UCLASS()
class AProgrammingTestHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProgrammingTestHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

