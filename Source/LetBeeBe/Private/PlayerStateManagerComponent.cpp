// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateManagerComponent.h"

#include "InteractionComponent.h"
#include "PlayerMovementComponent.h"
#include "WeaponManager.h"
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
		UPlayerMovementComponent* PlayerMovementComponent = Cast<UPlayerMovementComponent>(OwnerChar->GetCharacterMovement());
		UWeaponManager* WeaponManager = OwnerChar->GetComponentByClass<UWeaponManager>();
		switch (CurrentState)
		{
		case EPlayerState::Carrying:
			PlayerMovementComponent->MaxWalkSpeed *= 0.75f;
			PlayerMovementComponent->OnAim.Execute(false);
			WeaponManager->SetCanUseGun(false);
			WeaponManager->SetCanBuyWeapon(false);
			OwnerChar->GetComponentByClass<UInteractionComponent>()->SetCanInteract(false);
			break;
		default:
			OwnerChar->GetCharacterMovement()->MaxWalkSpeed = 300.f;
			WeaponManager->SetCanUseGun(true);
			WeaponManager->SetCanBuyWeapon(true);
			OwnerChar->GetComponentByClass<UInteractionComponent>()->SetCanInteract(true);
		
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
	return CurrentState == EPlayerState::Default;
}



