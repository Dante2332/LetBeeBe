// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "WeaponPickup.generated.h"

class USphereComponent;
class UWeaponDataAsset;

UCLASS()
class LETBEEBE_API AWeaponPickup : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void HandleInteract(AActor* Interactor) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponDataAsset* WeaponDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Cost;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:

};
