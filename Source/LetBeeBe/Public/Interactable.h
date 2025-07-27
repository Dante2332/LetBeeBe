// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Interactable.generated.h"

UCLASS()
class LETBEEBE_API AInteractable : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();
	virtual void SetCanInteract(bool bNewState) override { bCanInteract = bNewState; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool GetCanInteract() const override { return bCanInteract;}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereCollision;
	bool bCanInteract = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
