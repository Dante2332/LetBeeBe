// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class LETBEEBE_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();
	UFUNCTION()
	void HandleShoot();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float Damage;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void BindHandleShoot();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WeaponMesh;
};
