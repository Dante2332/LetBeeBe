// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildUI.h"
#include "BuildSubsystem.h"
#include "Components/ProgressBar.h"


void UBuildUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
	BindOnProgressChange();
}

void UBuildUI::BindOnProgressChange()
{
	UBuildSubsystem* BuildSubsystem = GetWorld()->GetSubsystem<UBuildSubsystem>();
	BuildSubsystem->OnBuildProgress.AddDynamic(this, &UBuildUI::HandleProgressChange);
}

void UBuildUI::HandleProgressChange(float Progress)
{
	BuildProgressBar->SetPercent(Progress);
}

