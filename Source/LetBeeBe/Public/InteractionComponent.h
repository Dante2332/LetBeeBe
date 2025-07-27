// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETBEEBE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Sprawdza co gracz ma przed sobą i ustawia aktualnego aktora do interakcji */
	void CheckForInteraction();

	/** Wykonuje interakcję z aktualnym obiektem */
	void Interact();

	/** Czy komponent pozwala na interakcję */
	void SetCanInteract(bool bNewState) { bCanInteract = bNewState; }

protected:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	bool bCanInteract = true;

	/** Aktor aktualnie "namierzony" przez gracza */
	UPROPERTY()
	AActor* CurrentInteractable = nullptr;

	FTimerHandle InteractionCheckHandle;

	/** Pokazuje prompt na HUD */
	void ShowPromptOnHUD(const FText& Prompt);

	/** Ukrywa prompt */
	void HidePromptOnHUD();
};
