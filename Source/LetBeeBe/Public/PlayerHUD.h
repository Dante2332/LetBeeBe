// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


class ALetBeeBeCharacter;
struct FTimeline;
/**
 * 
 */
UCLASS()
class LETBEEBE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APlayerHUD();
	~APlayerHUD();
	virtual void DrawHUD() override;
	float StartCrosshairGap = 15.0f;
	float AimingCrosshairGap = 6.0f;
	float CrosshairGap = 15.0f;

private:
	UFUNCTION()
	void HandleCameraZoomProgress(const float Value);
	void BindCameraZoomCurve();
	void BindAimHandle();
	void AimHandle(bool bIsAiming);
	ALetBeeBeCharacter* GetPlayerCharacter() const;
	
	//Timeline for aiming
	FTimeline* CameraZoomTimeline;
	UPROPERTY(EditAnywhere, Category = Camera)
	UCurveFloat* CameraZoomCurve;
protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
};
