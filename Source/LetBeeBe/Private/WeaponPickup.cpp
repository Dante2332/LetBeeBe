// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include "Gun.h"
#include "WeaponDataAsset.h"
#include "Components/SphereComponent.h"
// Sets default values
AWeaponPickup::AWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetSphereRadius(200);
	RootComponent = SphereCollision;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	DrawDebugSphere(GetWorld(), SphereCollision->GetComponentLocation(),SphereCollision->GetScaledSphereRadius(), 32, FColor::White, true);
	Super::BeginPlay();
	WeaponMesh->SetSkeletalMesh(WeaponDataAsset->WeaponInfo.WeaponMesh);
	Cost = WeaponDataAsset->WeaponInfo.Cost;
}

// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

