// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UShootComponent;
class UAmmoComponent;
enum class EWeaponType : uint8;
class UWeaponDataAsset;
class UPlayerMovementComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponDataAssetInitialized, UWeaponDataAsset*)

UCLASS()
class LETBEEBE_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();
	FOnWeaponDataAssetInitialized OnWeaponDataAssetInitialized;
	
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;
	FORCEINLINE UAmmoComponent* GetAmmoComponent() const { return AmmoComponent; } 
	FORCEINLINE UShootComponent* GetShootComponent() const { return ShootComponent; } 
	UPlayerMovementComponent* GetPlayerMovementComponent() const;

private:
	UPROPERTY(VisibleAnywhere)
	UAmmoComponent* AmmoComponent;
	UPROPERTY(VisibleAnywhere)
	UShootComponent* ShootComponent;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	void InitializeWeaponProperties();
	

};
