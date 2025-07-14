// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UInteractionWidget;
class UBuildUI;
class UCrosshairUI;


UCLASS()
class LETBEEBE_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	UCrosshairUI* GetCrosshairUI() const;
	UFUNCTION(BlueprintCallable)
	UBuildUI* GetBuildUI() const;
	UFUNCTION(BlueprintCallable)
	UInteractionWidget* GetInteractionWidget() const;
	void ShowBuildUI();
	void HideBuildUI();
	void ShowInteractionUI(const FText& NewText);
	void HideInteractionUI();
private:
	UPROPERTY(meta = (BindWidget))
	UCrosshairUI* CrosshairUI;
	UPROPERTY(meta = (BindWidget))
	UBuildUI* BuildUI;
	UPROPERTY(meta = (BindWidget))
	UInteractionWidget* InteractionWidget;
};
