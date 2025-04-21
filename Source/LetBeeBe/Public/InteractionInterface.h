// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class IInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void HandleInteract(AActor* Interactor) = 0;
	virtual FText GetInteractionText() const { return FText::FromString(TEXT("Interact")); }
	virtual bool GetCanInteract() const = 0;
	virtual void SetCanInteract(bool bNewState) = 0;
};