// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "PlayerMovementComponent.h"
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
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::HandleShoot()
{
	if (bIsReloading || ClipCurrentAmmo <= 0) return;
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
		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Red, TEXT("shot"));
		DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
	}
	--ClipCurrentAmmo;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Ammo After Shooting: %d"), ClipCurrentAmmo));
}

void AGun::BindHandleShoot()
{
	ALetBeeBeCharacter* Player = Cast<ALetBeeBeCharacter>(GetOwner());
	if (Player)
	{
		UPlayerMovementComponent* MovementComponent = Player->FindComponentByClass<UPlayerMovementComponent>();
		MovementComponent->OnShoot.AddDynamic(this, &AGun::HandleShoot);
	}
}

void AGun::StartReloading()
{
	if (bIsReloading || ClipCurrentAmmo == ClipSize || TotalAmmo <= 0) return;
		bIsReloading = true;
		GetWorld()->GetTimerManager().SetTimer(
			ReloadTimer,
			this,
			&AGun::HandleReload,
			ReloadSpeed,
			false
		);
}

void AGun::BindStartReloading()
{
	ALetBeeBeCharacter* Player = Cast<ALetBeeBeCharacter>(GetOwner());
	if (Player)
	{
		UPlayerMovementComponent* MovementComponent = Player->FindComponentByClass<UPlayerMovementComponent>();
		MovementComponent->OnReload.AddDynamic(this, &AGun::StartReloading);
	}
}

void AGun::HandleReload()
{
	int32 AmmoToReload = FMath::Min(ClipSize - ClipCurrentAmmo, TotalAmmo);
	ClipCurrentAmmo += AmmoToReload;
	TotalAmmo -= AmmoToReload;
	bIsReloading = false;
}