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
	
	Damage = 15.0f;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	BindHandleShoot();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::HandleShoot()
{
	/*DrawDebugSphere(GetWorld(), Start, 50, 50, FColor::Blue, false, 15);
	DrawDebugSphere(GetWorld(), End, 50, 50, FColor::Green, false, 15);*/
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

