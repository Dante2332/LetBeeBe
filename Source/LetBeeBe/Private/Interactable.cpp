// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

#include "PlayerMovementComponent.h"
#include "LetBeeBe/LetBeeBeCharacter.h"


// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetSphereRadius(200);
	RootComponent = SphereCollision;
}

void AInteractable::HandleInteract(AActor* Interactor)
{
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	BindHandleInteract();
	
	DrawDebugSphere(GetWorld(), SphereCollision->GetComponentLocation(),SphereCollision->GetScaledSphereRadius(), 32, FColor::White, true);
}



void AInteractable::BindHandleInteract()
{
	ALetBeeBeCharacter* PlayerCharacter = Cast<ALetBeeBeCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	PlayerCharacter->FindComponentByClass<UPlayerMovementComponent>()->OnInteract.AddUObject(this, &AInteractable::HandleInteract);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Bind: %s"), *this->GetName()));

}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

