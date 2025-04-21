// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateManagerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UPlayerStateManagerComponent::UPlayerStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentState = EPlayerState::Default;
}


// Called when the game starts
void UPlayerStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPlayerStateManagerComponent::SetState(EPlayerState NewState)
{
	CurrentState = NewState;

	if (ACharacter* OwnerChar = Cast<ACharacter>(GetOwner()))
	{
		switch (CurrentState)
		{
		case EPlayerState::Carrying:
			OwnerChar->GetCharacterMovement()->MaxWalkSpeed *= 0.75f;
			break;
		default:
			OwnerChar->GetCharacterMovement()->MaxWalkSpeed = 300.f;
		
		}
	}
}
bool UPlayerStateManagerComponent::CanPlaceBeelder() const
{
	return CurrentState == EPlayerState::Carrying;
}

bool UPlayerStateManagerComponent::CanJump() const
{
	return CurrentState != EPlayerState::Carrying;
}
bool UPlayerStateManagerComponent::CanShoot() const
{
	return CurrentState == EPlayerState::Default || CurrentState == EPlayerState::Aiming;
}



