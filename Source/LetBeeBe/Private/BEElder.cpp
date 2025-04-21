// Fill out your copyright notice in the Description page of Project Settings.


#include "BEElder.h"

#include "MovieSceneTracksComponentTypes.h"
#include "WeaponManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LetBeeBe/LetBeeBeCharacter.h"

ABEElder::ABEElder()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}
void ABEElder::HandleInteract(AActor* Interactor)
{
	if (!bCanInteract) return;
	if (bIsPicked)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Drop interacted");

		Drop();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pick interacted");

		Pickup();
	}
}
void ABEElder::Pickup()
{
	bIsPicked = true;
	ALetBeeBeCharacter* Player = Cast<ALetBeeBeCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UWeaponManager* WeaponManager = Player->GetWeaponManager();
	WeaponManager->SetCanUseGun(false);
	AttachToComponent(Player->GetBeelderAttachment(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Picked up");
	
}

void ABEElder::Drop()
{
	bIsPicked = false;
	ALetBeeBeCharacter* Player = Cast<ALetBeeBeCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UWeaponManager* WeaponManager = Player->GetWeaponManager();
	WeaponManager->SetCanUseGun(true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "dropped");
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
	
}

void ABEElder::Tick(float DeltaTime)
{
	
}
