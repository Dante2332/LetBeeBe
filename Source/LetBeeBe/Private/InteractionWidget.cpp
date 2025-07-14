// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UInteractionWidget::SetPromptText(const FText& NewText)
{
	PromptText->SetText(NewText);
}

void UInteractionWidget::ShowProgressBar()
{
	ProgressBar->SetVisibility(ESlateVisibility::Visible);
}

void UInteractionWidget::HideProgressBar()
{
	ProgressBar->SetVisibility(ESlateVisibility::Hidden);
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HideProgressBar();
	SetVisibility(ESlateVisibility::Hidden);
}
