// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "InteractionInterface.h"
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
	if (OtherActor && OtherActor->Implements<UInteractionInterface>())
	{
		OverlappingActors.Add(OtherActor);
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, FName("CheckForInteraction"), OverlappingActors);
		GetWorld()->GetTimerManager().SetTimer(InteractionTimeHandle, Delegate, 0.2f, true);
		
	}
}

void UInteractionComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
														UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if (OtherActor && OtherActor->Implements<UInteractionInterface>())
	{
		IInteractionInterface* OverlappedActor = Cast<IInteractionInterface>(OtherActor);
		if (OverlappedActor->GetCanInteract())
		{
			OverlappedActor->SetCanInteract(false);
			if (OverlappingActors.Contains(OtherActor))
			{
				OverlappingActors.Remove(OtherActor);
			}
		}
		if (OverlappingActors.IsEmpty())
		{
			GetWorld()->GetTimerManager().ClearTimer(InteractionTimeHandle);
		}
		
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("EndOverlapActor: %s"), *OtherActor->GetName()));

	}
}

void UInteractionComponent::CheckForInteraction(TArray<AActor*> ActorsToCheck)
{
	for (AActor* Actor : ActorsToCheck)
	{
		IInteractionInterface* OverlappedActor = Cast<IInteractionInterface>(Actor);
		if (!OverlappedActor) return; 
		FHitResult Hit;
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = Start + GetOwner()->GetActorForwardVector() * 100.0f;
		if ( GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
		{
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
				if (OverlappingActors.Contains(Actor))
				{
					OverlappingActors.Remove(Actor);
				}
			}
		}
	}
}

