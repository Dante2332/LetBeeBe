// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManager.h"

#include "EditorCategoryUtils.h"
#include "Gun.h"
#include "PlayerMovementComponent.h"
#include "ShootComponent.h"
#include "AmmoComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



// Called when the game starts
void UWeaponManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon(SecondaryWeaponClass);
	 
	BindWeaponSwitchHandle();
}


// Called every frame
void UWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UWeaponManager::BindWeaponSwitchHandle()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	UPlayerMovementComponent* PlayerMovementComponent = Cast<UPlayerMovementComponent>(PlayerController->GetPawn()->GetMovementComponent());
	PlayerMovementComponent->OnWeaponSwitch.BindUObject(this, &UWeaponManager::SwitchWeapon);
}


void UWeaponManager::SwitchWeapon(int32 WeaponIndex)
{
	EquippedWeapon->GetShootComponent()->StopShooting();
	
	switch (WeaponIndex)
	{
	case 1:
		// Check if Primary Weapon should be equipped
		if (EquippedWeapon->GetClass() != SecondaryWeaponClass) return;
		break;
	case 2:
		//Check if Secondary Weapon should be equipped
		if (EquippedWeapon->GetClass() == SecondaryWeaponClass) return;
		break;
	default:
		break;
	}
	if (HiddenWeapon)
	{
		EquipWeapon(HiddenWeapon);
		EquippedWeapon->GetShootComponent()->Reinitialize();
		EquippedWeapon->GetAmmoComponent()->Reinitialize();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("Equipped Weapon: %s"), *EquippedWeapon->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Ammo Component Owner: %s"), *EquippedWeapon->GetAmmoComponent()->GetOwner()->GetName()));
	}
}
void UWeaponManager::SpawnWeapon(const TSubclassOf<AGun>& WeaponToSpawn)
{
	if (EquippedWeapon && EquippedWeapon->GetClass() != SecondaryWeaponClass)
	{
		EquippedWeapon->Destroy();
		// if (HiddenWeapon->GetClass() != SecondaryWeaponClass)
		// {
		// 	HiddenWeapon->Destroy();
		// }
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	AGun* SpawnedWeapon = GetWorld()->SpawnActor<AGun>(WeaponToSpawn, SpawnParameters);
	SpawnedWeapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "weapon_R");
	SpawnedWeapon->SetOwner(GetOwner());
	EquipWeapon(SpawnedWeapon);
}

void UWeaponManager::EquipWeapon(AGun* WeaponToEquip)
{
	if (!bCanUseGun) return;
		// Null Check
	if (!EquippedWeapon)
	{
		EquippedWeapon = WeaponToEquip;
	}
	else
	{
		//Hide Old Weapon
		EquippedWeapon->SetActorEnableCollision(false);
		EquippedWeapon->SetActorHiddenInGame(true);
		HiddenWeapon = EquippedWeapon;
		// Equip New Weapon
		EquippedWeapon = WeaponToEquip;
		EquippedWeapon->SetActorEnableCollision(true);
		EquippedWeapon->SetActorHiddenInGame(false);
		// Set correct components
		EquippedWeapon->GetShootComponent()->Reinitialize();
		EquippedWeapon->GetAmmoComponent()->Reinitialize();
	}
	
}


void UWeaponManager::BuyWeapon(const TSubclassOf<AGun>& WeaponToBuy)
{
	if (WeaponToBuy == EquippedWeapon->GetClass())
	{
		return;
	}
	if (HiddenWeapon && WeaponToBuy == HiddenWeapon->GetClass())
	{
		return;
	}
	
	SpawnWeapon(WeaponToBuy);
	GEngine->AddOnScreenDebugMessage(-1,	10.0f, FColor::Red, FString::Printf(TEXT("Spawned Weapon")));
}

void UWeaponManager::DisableWeapon()
{
	if (!EquippedWeapon) return;
	EquippedWeapon->SetActorEnableCollision(false);
	EquippedWeapon->SetActorHiddenInGame(true);
	bCanUseGun = false;
}
void UWeaponManager::UnableWeapon()
{
	EquippedWeapon->SetActorEnableCollision(true);
	EquippedWeapon->SetActorHiddenInGame(false);
	bCanUseGun = true;
}
void UWeaponManager::SetCanUseGun(bool bNewState)
{
	bCanUseGun = bNewState;
	if (bCanUseGun)
	{
		UnableWeapon();
	}
	else
	{
		DisableWeapon();
	}
}
