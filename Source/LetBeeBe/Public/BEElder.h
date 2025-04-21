// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "BEElder.generated.h"

/**
 * 
 */
UCLASS()
class LETBEEBE_API ABEElder : public AInteractable
{
	GENERATED_BODY()

public:
	ABEElder();
	virtual void HandleInteract(AActor* Interactor) override;
	virtual void Tick(float DeltaTime) override;
	
private:
	void Pickup();
	void Drop();
	bool bIsPicked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;
};
