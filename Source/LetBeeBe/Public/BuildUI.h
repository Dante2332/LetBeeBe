// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildUI.generated.h"

/**
 * 
 */
UCLASS()
class LETBEEBE_API UBuildUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* BuildCanvas;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* BuildProgressBar;
private:
	void BindOnProgressChange();
	UFUNCTION()
	void HandleProgressChange(float Progress);

};
