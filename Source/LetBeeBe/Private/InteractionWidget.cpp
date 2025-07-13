// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"

#include "Components/TextBlock.h"

void UInteractionWidget::SetPromptText(const FText& NewText)
{
	PromptText->SetText(NewText);
}

void UInteractionWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UInteractionWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Hide();
}
