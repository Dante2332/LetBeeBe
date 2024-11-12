// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();

	if (Canvas)
	{
		// Get screen center
		const float CenterX = Canvas->ClipX / 2.0f;
		const float CenterY = Canvas->ClipY / 2.0f;

		// Set crosshair lines length
		const float LineLength = 10.f;

		FLinearColor CrosshairColor = FLinearColor::White;

		DrawLine(CenterX - CrosshairGap - LineLength, CenterY, CenterX - CrosshairGap, CenterY, CrosshairColor);
		DrawLine(CenterX + CrosshairGap, CenterY, CenterX + CrosshairGap + LineLength, CenterY, CrosshairColor);
		DrawLine(CenterX, CenterY - CrosshairGap - LineLength, CenterX, CenterY - CrosshairGap, CrosshairColor);
		DrawLine(CenterX, CenterY + CrosshairGap, CenterX, CenterY + CrosshairGap + LineLength , CrosshairColor);
	}
}

