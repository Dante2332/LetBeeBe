// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoComponent.generated.h"


class UShootComponent;
class UWeaponDataAsset;
class AGun;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETBEEBE_API UAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void Reinitialize();
	// Sets default values for this component's properties
	UAmmoComponent();
	void DecrementAmmo();
	FORCEINLINE void SetOwner(AGun* Owner) {GunOwner = Owner;}
	FORCEINLINE int GetClipCurrentAmmo() const { return ClipCurrentAmmo; }
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	FTimerHandle ReloadTimer;
	UPROPERTY()
	AGun* GunOwner;
	void BindHandleInitialize();
	void HandleInitialize(UWeaponDataAsset* DataAsset);
	int32 TotalAmmo;
	int32 ClipSize;
	int32 ClipCurrentAmmo;
	float ReloadSpeed;
	void HandleReload();
	void BindStartReloading();
	void StartReloading();
	UPROPERTY()
	UShootComponent* ShootComponent;

		
};
