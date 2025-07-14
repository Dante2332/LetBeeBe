// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

#include "BuildUI.h"
#include "InteractionWidget.h"

UCrosshairUI* UPlayerWidget::GetCrosshairUI() const
{
	return CrosshairUI;
}

UBuildUI* UPlayerWidget::GetBuildUI() const
{
	return BuildUI;
}

UInteractionWidget* UPlayerWidget::GetInteractionWidget() const
{
	return InteractionWidget;
}

void UPlayerWidget::ShowBuildUI()
{
	BuildUI->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerWidget::HideBuildUI()
{
	BuildUI->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWidget::ShowInteractionUI(const FText& NewText)
{
	InteractionWidget->SetPromptText(NewText);
	InteractionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerWidget::HideInteractionUI()
{
	InteractionWidget->SetVisibility(ESlateVisibility::Hidden);
}
