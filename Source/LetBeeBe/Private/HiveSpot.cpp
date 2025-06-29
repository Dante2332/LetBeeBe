// Fill out your copyright notice in the Description page of Project Settings.


#include "HiveSpot.h"

#include "Components/SphereComponent.h"

// Sets default values
AHiveSpot::AHiveSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	RootComponent = DefaultRoot;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetSphereRadius(100);
	BEElderPlacement = CreateDefaultSubobject<USceneComponent>(TEXT("BEElderPlacement"));
	BEElderPlacement->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHiveSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHiveSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

