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
	UFUNCTION()
	void StartReloading();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float Damage = 15.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int32 TotalAmmo = 42;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float ReloadSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	int32 ClipSize;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Stats")
	int32 ClipCurrentAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsReloading;
	
	FTimerHandle ReloadTimer;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void BindHandleShoot();
	void HandleReload();
	void BindStartReloading();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* WeaponMesh;
};
