// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "Interactable.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InteractionSphere = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	InteractionSphere->SetSphereRadius(100);
	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::OnSphereBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::OnSphereEndOverlap);
	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}
void UInteractionComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
																			int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Interactable"))
	{
		
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, FName("CheckForInteraction"), OtherActor);
		GetWorld()->GetTimerManager().SetTimer(InteractionTimeHandle, Delegate, 0.2f, true);
		
		
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("OverlappedActor: %s"), *OtherActor->GetName()));
	}
}

void UInteractionComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
														UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Interactable"))
	{
		AInteractable* OverlappedActor = Cast<AInteractable>(OtherActor);
		GetWorld()->GetTimerManager().ClearTimer(InteractionTimeHandle);
		if (OverlappedActor->GetCanInteract())
		{
			OverlappedActor->SetCanInteract(false);
		}
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("EndOverlapActor: %s"), *OtherActor->GetName()));

	}
}

void UInteractionComponent::CheckForInteraction(AActor* ActorToCheck)
{
	AInteractable* OverlappedActor = Cast<AInteractable>(ActorToCheck);
	FHitResult Hit;
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + GetOwner()->GetActorForwardVector() * 100.0f;
	if ( GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("CanInteract")));
		if (!OverlappedActor->GetCanInteract())
		{
			OverlappedActor->SetCanInteract(true);
		}
	}
	else
	{
		if (OverlappedActor->GetCanInteract())
		{
			OverlappedActor->SetCanInteract(false);
		}
	}
}

