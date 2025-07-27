// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"


// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetSphereRadius(200);
	RootComponent = SphereCollision;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugSphere(GetWorld(), SphereCollision->GetComponentLocation(),SphereCollision->GetScaledSphereRadius(), 32, FColor::White, true);
}



// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

