// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "PlayerMovementComponent.h"
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
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	ClipCurrentAmmo = ClipSize;
	Super::BeginPlay();
	BindHandleShoot();
	BindStartReloading();
	InitializeWeaponProperties();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGun::BindStartReloading()
{
	GetPlayerMovementComponent()->OnReload.BindUObject(this, &AGun::StartReloading);
}
void AGun::BindHandleShoot()
{
	GetPlayerMovementComponent()->OnShoot.BindUObject(this, &AGun::HandleShoot);
}

void AGun::HandleShoot(bool bShouldShoot)
{
	bShouldShoot ? StartShooting() : StopShooting();
}

void AGun::Fire()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	AController* Controller = OwnerPawn->GetController();
	if (!Controller) return;
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
	--ClipCurrentAmmo;
	if (ClipCurrentAmmo == 0 || bIsShooting)
	{
		StopShooting();
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Ammo After Shooting: %d"), ClipCurrentAmmo));
}

void AGun::StartShooting()
{
	if (bIsReloading || ClipCurrentAmmo <= 0) return;
	if (bIsFullAuto)
	{
		bIsShooting = true;
		Fire();
		GetWorld()->GetTimerManager().SetTimer(FullAutoFireTimer, this, &AGun::Fire, RateOfFire, true);
	}
	else
	{
		Fire();
	}
}
void AGun::StopShooting()
{
	if (bIsFullAuto)
	{
		bIsShooting = false;
		GetWorld()->GetTimerManager().ClearTimer(FullAutoFireTimer);
	}
}

void AGun::StartReloading()
{
	if (bIsReloading || ClipCurrentAmmo == ClipSize || TotalAmmo <= 0) return;
		bIsReloading = true;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimer,this, &AGun::HandleReload,ReloadSpeed,false);
}
void AGun::HandleReload()
{
	int32 AmmoToReload = FMath::Min(ClipSize - ClipCurrentAmmo, TotalAmmo);
	ClipCurrentAmmo += AmmoToReload;
	TotalAmmo -= AmmoToReload;
	bIsReloading = false;
}


UPlayerMovementComponent* AGun::GetPlayerMovementComponent() const
{
	ALetBeeBeCharacter* Player = Cast<ALetBeeBeCharacter>(GetOwner());
	if (Player)
	{
		return Player->FindComponentByClass<UPlayerMovementComponent>();
	}
	return nullptr;
}

void AGun::InitializeWeaponProperties()
{
	WeaponMesh->SetSkeletalMesh(WeaponDataAsset->WeaponInfo.WeaponMesh);
	ClipSize = WeaponDataAsset->WeaponInfo.ClipSize;
	WeaponName = WeaponDataAsset->WeaponInfo.Name;
	Damage = WeaponDataAsset->WeaponInfo.Damage;
	RateOfFire = WeaponDataAsset->WeaponInfo.RateOfFire;
	ReloadSpeed = WeaponDataAsset->WeaponInfo.ReloadSpeed;
	bIsFullAuto = WeaponDataAsset->WeaponInfo.bIsFullAuto;
	TotalAmmo = WeaponDataAsset->WeaponInfo.TotalAmmo;
	WeaponType = WeaponDataAsset->WeaponInfo.WeaponType;
	ClipCurrentAmmo = ClipSize;
}


