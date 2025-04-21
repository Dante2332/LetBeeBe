// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"

#include "AmmoComponent.h"
#include "Gun.h"
#include "PlayerMovementComponent.h"
#include "WeaponDataAsset.h"


// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();
	GunOwner = Cast<AGun>(GetOwner());
	AmmoComponent = GunOwner->GetAmmoComponent();
	BindHandleInitialize();
	BindHandleShoot();
}
void UShootComponent::BindHandleInitialize()
{
	if (GunOwner)
	{
		GunOwner->OnWeaponDataAssetInitialized.AddUObject(this, &UShootComponent::HandleInitialize);
	}
}

void UShootComponent::HandleInitialize(UWeaponDataAsset* DataAsset)
{
	Damage = DataAsset->WeaponInfo.Damage;
	RateOfFire = DataAsset->WeaponInfo.RateOfFire;
	bIsFullAuto = DataAsset->WeaponInfo.bIsFullAuto;
}

void UShootComponent::BindHandleShoot()
{
	GunOwner->GetPlayerMovementComponent()->OnShoot.BindUObject(this, &UShootComponent::HandleShoot);
}

void UShootComponent::HandleShoot(bool bShouldShoot)
{
	if (bShouldShoot && !GunOwner->IsHidden())
	{
		StartShooting();
	}
	else
	{
		StopShooting();
	}
	
}

void UShootComponent::Fire()
{
	//Check for nullptrs
	APawn* OwnerPawn = Cast<APawn>(GetOwner()->GetOwner());
	if (!OwnerPawn) return;
	AController* Controller = OwnerPawn->GetController();
	if (!Controller) return;
	//Set LineTrace params
	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	Params.AddIgnoredActor(OwnerPawn);
	FVector EndLocation = Location + Rotation.Vector() * 5000;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Location, EndLocation, ECC_GameTraceChannel1, Params))
		{
			DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		}
	// Handle Ammo Change
	AmmoComponent->DecrementAmmo();
	if (AmmoComponent->GetClipCurrentAmmo() == 0 || bIsShooting)
		{
			StopShooting();
		}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Ammo After Shooting: %d"), AmmoComponent->GetClipCurrentAmmo()));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Owner: %s"), *GunOwner->GetName()));
}

void UShootComponent::StartShooting()
{
	if (bIsReloading || AmmoComponent->GetClipCurrentAmmo() <= 0) return;
	if (bIsFullAuto)
	{

		bIsShooting = true;
		Fire();
		GetWorld()->GetTimerManager().SetTimer(FullAutoFireTimer, this, &UShootComponent::Fire, RateOfFire, true);
		
	}
	else
	{
		Fire();
	}
}
void UShootComponent::StopShooting()
{
	if (bIsFullAuto)
	{
		bIsShooting = false;
		GetWorld()->GetTimerManager().ClearTimer(FullAutoFireTimer);
	}
}
void UShootComponent::Reinitialize()
{
	GunOwner = Cast<AGun>(GetOwner());
	AmmoComponent = GunOwner ? GunOwner->GetAmmoComponent() : nullptr;

	// Ponowne bindowanie zdarzeń
	BindHandleInitialize();
	BindHandleShoot();
}
