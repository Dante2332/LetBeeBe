// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

UCrosshairUI* UPlayerWidget::GetCrosshairUI() const
{
	return CrosshairUI;
}

UBuildUI* UPlayerWidget::GetBuildUI() const
{
	return BuildUI;
}