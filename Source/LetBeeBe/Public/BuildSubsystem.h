// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BuildSubsystem.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildEndSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildProgressSignature, float, Progress);

class ABEElder;
/**
 * 
 */
UCLASS()
class LETBEEBE_API UBuildSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	FOnBuildStartedSignature OnBuildStart;
	FOnBuildEndSignature OnBuildEnd;
	FOnBuildProgressSignature OnBuildProgress;
	void StartBuild(ABEElder* Beelder);

private:
	FTimerHandle BuildTimerHandle;
	float CurrentProgress;
	UFUNCTION()
	void UpdateBuildProgress();
	void FinishBuild();
};
