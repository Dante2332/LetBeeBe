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
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Shot"));
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

