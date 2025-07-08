// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairUI.generated.h"


UCLASS()
class LETBEEBE_API UCrosshairUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetCrosshairGap(float Gap);

private:

protected:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CrosshairCanvas;

	UPROPERTY(meta = (BindWidget))
	class UImage* TopLine;
	UPROPERTY(meta = (BindWidget))
	class UImage* BottomLine;
	UPROPERTY(meta = (BindWidget))
	class UImage* LeftLine;
	UPROPERTY(meta = (BindWidget))
	class UImage* RightLine;
};

