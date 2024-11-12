// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class LETBEEBE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;
	float StartCrosshairGap = 15.0f;
	float AimingCrosshairGap = 6.0f;
	float CrosshairGap = 15.0f;


private:

};