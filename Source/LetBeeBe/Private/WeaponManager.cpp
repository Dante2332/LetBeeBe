// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManager.h"

#include "EditorCategoryUtils.h"
#include "Gun.h"
#include "PlayerMovementComponent.h"
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
	SpawnSecondary();
	SecondaryWeapon->SetActorHiddenInGame(true);
	SecondaryWeapon->SetActorEnableCollision(false);
	SpawnPrimary();
	BindWeaponSwitchHandle();
}


// Called every frame
void UWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Spawn Secondary Weapon at BeginPlay
void UWeaponManager::SpawnSecondary()
{
	if (!SecondaryWeapon)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SecondaryWeapon = GetWorld()->SpawnActor<AGun>(SecondaryWeaponClass, SpawnParameters);
		SecondaryWeapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "weapon_r");
		SecondaryWeapon->SetOwner(GetOwner());
		EquippedWeapon = SecondaryWeapon;
	}
}
void UWeaponManager::SpawnPrimary()
{
	if (PrimaryWeapon)
	{
		PrimaryWeapon->Destroy();
	}
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		PrimaryWeapon = GetWorld()->SpawnActor<AGun>(PrimaryWeaponClass, SpawnParameters);
		PrimaryWeapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "weapon_R");
		PrimaryWeapon->SetOwner(GetOwner());
		EquippedWeapon = PrimaryWeapon;
}

void UWeaponManager::EquipPrimary()
{
	if (PrimaryWeapon)
	{
		SecondaryWeapon->SetActorEnableCollision(false);
		SecondaryWeapon->SetActorHiddenInGame(true);
		PrimaryWeapon->SetActorEnableCollision(true);
		PrimaryWeapon->SetActorHiddenInGame(false);
		EquippedWeapon = PrimaryWeapon;
	}
}

void UWeaponManager::EquipSecondary()
{
	if (EquippedWeapon == SecondaryWeapon) return;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Secondary Equipped"));

	SecondaryWeapon->SetActorEnableCollision(true);
	SecondaryWeapon->SetActorHiddenInGame(false);
	PrimaryWeapon->SetActorEnableCollision(false);
	PrimaryWeapon->SetActorHiddenInGame(true);
	EquippedWeapon = SecondaryWeapon;
}
void UWeaponManager::BindWeaponSwitchHandle()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	UPlayerMovementComponent* PlayerMovementComponent = Cast<UPlayerMovementComponent>(PlayerController->GetPawn()->GetMovementComponent());
	PlayerMovementComponent->OnWeaponSwitch.BindUObject(this, &UWeaponManager::SwitchWeapon);
}


void UWeaponManager::SwitchWeapon(int32 WeaponIndex)
{
	switch (WeaponIndex)
	{
	case 1:
		EquipPrimary();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Primary Equipped"));
		break;
	case 2:

		EquipSecondary();

		break;
	default:
		break;
			
	}
}



