// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include "WeaponDataAsset.h"
#include "LetBeeBe/LetBeeBeCharacter.h"
#include "WeaponManager.h"
#include "Gun.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	
	Super::BeginPlay();
	WeaponMesh->SetSkeletalMesh(WeaponDataAsset->WeaponInfo.WeaponMesh);
	Cost = WeaponDataAsset->WeaponInfo.Cost;
}

void AWeaponPickup::HandleInteract()
{
	if (bCanInteract)
	{
		ALetBeeBeCharacter* PlayerCharacter = Cast<ALetBeeBeCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		UWeaponManager* WeaponManager = PlayerCharacter->GetWeaponManager();
		WeaponManager->BuyWeapon(WeaponDataAsset->WeaponInfo.WeaponClass);
	}
	
}



// Called every frame
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
