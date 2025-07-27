// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSubsystem.h"
#include "BEElder.h"
#include "EngineUtils.h"


void UBuildSubsystem::StartBuild(ABEElder* BEElder)
{
	OnBuildStart.Broadcast();
	BEElder->SetCanInteract(false);
	CurrentProgress = 0.0f;
	GetWorld()->GetTimerManager().SetTimer(BuildTimerHandle, this, &UBuildSubsystem::UpdateBuildProgress, 0.1f, true);
}
void UBuildSubsystem::FinishBuild()
{
	GetWorld()->GetTimerManager().ClearTimer(BuildTimerHandle);
	OnBuildEnd.Broadcast();
	for (TActorIterator<ABEElder> It(GetWorld()); It; ++It)
	{
		ABEElder* Beelder = *It;
		if (Beelder)
		{
			Beelder->SetCanInteract(true);
		}
	}
	
}

void UBuildSubsystem::UpdateBuildProgress()
{
	CurrentProgress += 0.083f;
	OnBuildProgress.Broadcast(CurrentProgress);
	if (CurrentProgress >= 1.0f)
	{
		FinishBuild();
	}
}

