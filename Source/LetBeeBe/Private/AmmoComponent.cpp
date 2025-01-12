// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoComponent.h"
#include "Gun.h"
#include "ShootComponent.h"
#include "WeaponDataAsset.h"
#include "PlayerMovementComponent.h"
#include "WeaponManager.h"
// Sets default values for this component's properties
UAmmoComponent::UAmmoComponent()
{}

// Called when the game starts
void UAmmoComponent::BeginPlay()
{
	Super::BeginPlay();
	GunOwner = Cast<AGun>(GetOwner());
	ShootComponent = GunOwner->GetShootComponent();
	BindHandleInitialize();
	BindStartReloading();
}

void UAmmoComponent::BindHandleInitialize()
{
	if (GunOwner)
	{
		GunOwner->OnWeaponDataAssetInitialized.AddUObject(this, &UAmmoComponent::HandleInitialize);
	}
}

void UAmmoComponent::HandleInitialize(UWeaponDataAsset* DataAsset)
{
	TotalAmmo = DataAsset->WeaponInfo.TotalAmmo;
	ClipSize = DataAsset->WeaponInfo.ClipSize;
	ClipCurrentAmmo = ClipSize;
	ReloadSpeed = DataAsset->WeaponInfo.ReloadSpeed;
}
void UAmmoComponent::BindStartReloading()
{
	GunOwner->GetPlayerMovementComponent()->OnReload.BindUObject(this, &UAmmoComponent::StartReloading);
}

void UAmmoComponent::StartReloading()
{
	if (ShootComponent->GetIsReloading() || ClipCurrentAmmo == ClipSize || TotalAmmo <= 0) return;
	ShootComponent->SetIsReloading(true);
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer,this, &UAmmoComponent::HandleReload,ReloadSpeed,false);
}
void UAmmoComponent::HandleReload()
{
	int32 AmmoToReload = FMath::Min(ClipSize - ClipCurrentAmmo, TotalAmmo);
	ClipCurrentAmmo += AmmoToReload;
	TotalAmmo -= AmmoToReload;
	ShootComponent->SetIsReloading(false);
}

void UAmmoComponent::DecrementAmmo()
{
	--ClipCurrentAmmo;
}



