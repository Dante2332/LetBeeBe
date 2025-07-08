// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairUI.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

void UCrosshairUI::SetCrosshairGap(float Gap)
{
	if (!TopLine || !BottomLine || !LeftLine || !RightLine) return;

	// Góra
	if (UCanvasPanelSlot* TopSlot = Cast<UCanvasPanelSlot>(TopLine->Slot))
		TopSlot->SetPosition(FVector2D(0, -Gap));

	// Dół
	if (UCanvasPanelSlot* BottomSlot = Cast<UCanvasPanelSlot>(BottomLine->Slot))
		BottomSlot->SetPosition(FVector2D(0, Gap));

	// Lewo
	if (UCanvasPanelSlot* LeftSlot = Cast<UCanvasPanelSlot>(LeftLine->Slot))
		LeftSlot->SetPosition(FVector2D(-Gap, 0));

	// Prawo
	if (UCanvasPanelSlot* RightSlot = Cast<UCanvasPanelSlot>(RightLine->Slot))
		RightSlot->SetPosition(FVector2D(Gap, 0));
}
