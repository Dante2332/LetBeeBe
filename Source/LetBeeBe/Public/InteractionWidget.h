// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class LETBEEBE_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetPromptText(const FText& NewText);

	UFUNCTION(BlueprintCallable)
	void ShowProgressBar();

	UFUNCTION(BlueprintCallable)
	void HideProgressBar();

protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PromptText;
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalBox;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar;
};
