// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "AmmoComponent.h"
#include "PlayerMovementComponent.h"
#include "ShootComponent.h"
#include "WeaponDataAsset.h"
#include "LetBeeBe/LetBeeBeCharacter.h"


// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	WeaponMesh->SetupAttachment(Root);
	AmmoComponent = CreateDefaultSubobject<UAmmoComponent>("AmmoComponent");
	ShootComponent = CreateDefaultSubobject<UShootComponent>("ShootComponent");
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	ClipCurrentAmmo = ClipSize;
	Super::BeginPlay();

	InitializeWeaponProperties();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UPlayerMovementComponent* AGun::GetPlayerMovementComponent() const
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		ALetBeeBeCharacter* PlayerCharacter = Cast<ALetBeeBeCharacter>(PlayerController->GetPawn());
		
		if (PlayerCharacter)
		{
			return PlayerCharacter->FindComponentByClass<UPlayerMovementComponent>();
		}
		return nullptr;
	}
	return nullptr;
}

void AGun::InitializeWeaponProperties()
{
	OnWeaponDataAssetInitialized.Broadcast(WeaponDataAsset);
	WeaponMesh->SetSkeletalMesh(WeaponDataAsset->WeaponInfo.WeaponMesh);
	WeaponName = WeaponDataAsset->WeaponInfo.Name;
	WeaponType = WeaponDataAsset->WeaponInfo.WeaponType;
}


