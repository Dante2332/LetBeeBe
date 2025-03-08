// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Interactable.generated.h"

UCLASS()
class LETBEEBE_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();
	FORCEINLINE bool GetCanInteract() { return bCanInteract; } 
	FORCEINLINE void SetCanInteract(bool CanInteract) { bCanInteract = CanInteract; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereCollision;
	bool bCanInteract;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
