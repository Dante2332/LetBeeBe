// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"

class UAmmoComponent;
class AGun;
class UPlayerMovementComponent;
class UWeaponDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETBEEBE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShootComponent();
	FORCEINLINE bool GetIsReloading() {	return bIsReloading; }
	FORCEINLINE void SetIsReloading(bool b) {	bIsReloading = b; }
	
protected:
	virtual void BeginPlay() override;

private:
	float Damage;
	float RateOfFire;
	bool bIsFullAuto;
	bool bIsReloading;
	bool bIsShooting;
	FTimerHandle FullAutoFireTimer;
	void BindHandleShoot();
	void BindHandleInitialize();
	void HandleInitialize(UWeaponDataAsset* DataAsset);
	void HandleShoot(bool bShouldShoot);
	void Fire();
	void StartShooting();
	void StopShooting();
	UPROPERTY(EditAnywhere)
	AGun* GunOwner;
	UPROPERTY()
	UAmmoComponent* AmmoComponent;
};
