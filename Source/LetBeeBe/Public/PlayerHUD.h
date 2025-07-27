// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


class UPlayerWidget;
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
	UPlayerWidget* GetPlayerWidget() const;



private:
	float StartCrosshairGap = 35.f;
	float AimCrosshairGap = 12.f;
	
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UPlayerWidget> PlayerWidgetClass;

	UPROPERTY()
	UPlayerWidget* PlayerWidget;
	
	UFUNCTION()
	void HandleCameraZoomProgress(const float Value);
	void BindCameraZoomCurve();
	void BindAimHandle();
	void AimHandle(bool bIsAiming);
	ALetBeeBeCharacter* GetPlayerCharacter() const;
	void BindHandleBuildStart();
	UFUNCTION()
	void HandleBuildStart();
	void BindHandleBuildEnd();
	UFUNCTION()
	void HandleBuildEnd();
	void ShowBuildUI();
	void HideBuildUI();
	
	//Timeline for aiming
	FTimeline* CameraZoomTimeline;
	UPROPERTY(EditAnywhere, Category = Camera)
	UCurveFloat* CameraZoomCurve;
protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
};
