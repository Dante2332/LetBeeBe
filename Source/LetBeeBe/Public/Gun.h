// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"


enum class EWeaponType : uint8;
class UWeaponDataAsset;
class UPlayerMovementComponent;

UCLASS()
class LETBEEBE_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FName WeaponName;
	float Damage;
	bool bIsFullAuto;
	EWeaponType WeaponType;
	int32 TotalAmmo;
	int32 ClipSize;
	int32 ClipCurrentAmmo;
	float ReloadSpeed;
	float RateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponProperties")
	UWeaponDataAsset* WeaponDataAsset;
	
	FTimerHandle ReloadTimer;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;

private:
	UPROPERTY(VisibleAnywhere)
	bool bIsReloading;
	bool bIsShooting;
	FTimerHandle FullAutoFireTimer;
	void BindHandleShoot();
	void HandleReload();
	void BindStartReloading();
	void HandleShoot(bool bShouldShoot);
	void Fire();
	void StartShooting();
	void StopShooting();
	void StartReloading();

	UPlayerMovementComponent* GetPlayerMovementComponent() const;
	
	void InitializeWeaponProperties();
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	

};
