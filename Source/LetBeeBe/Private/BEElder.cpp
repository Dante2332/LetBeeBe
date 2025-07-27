// Fill out your copyright notice in the Description page of Project Settings.


#include "BEElder.h"

#include "BuildSubsystem.h"
#include "HiveSpot.h"
#include "PlayerStateManagerComponent.h"
#include "LetBeeBe/LetBeeBeCharacter.h"


ABEElder::ABEElder()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
}
void ABEElder::BeginPlay()
{
	Super::BeginPlay();
	
}

FText ABEElder::GetInteractionText() const
{
	if (!bIsBuilding)
	{
		return FText::FromString(TEXT("Press F to Pickup BEElder"));
	}
	else
	{
		return FText::FromString("Hold F To repair");
	}
}

void ABEElder::HandleInteract_Implementation(AActor* Interactor)
{
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
	AttachToComponent(Player->GetBeelderAttachment(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Picked up");
	Player->GetPlayerStateManager()->SetState(EPlayerState::Carrying);
	SphereCollision->SetSphereRadius(60.f);
	
}

bool ABEElder::Drop()
{
	if (!CanBeDropped()) return false;
	if (TryPlaceOnHiveSpot() || TryPlaceOnGround())
	{
		bIsPicked = false;
		ALetBeeBeCharacter* Player = Cast<ALetBeeBeCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "dropped");
		Player->GetPlayerStateManager()->SetState(EPlayerState::Default);
		SphereCollision->SetSphereRadius(200.f);
		return true;
	}
	return false;
}

bool ABEElder::CanBeDropped()
{
	return bIsPicked;
}

bool ABEElder::TryPlaceOnGround()
{
	FHitResult Hit;
	if (!TraceToGround(Hit)) return false;

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocation(Hit.ImpactPoint + GroundDropOffset);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "PlaceOnGround");
	return true;
	
}

bool ABEElder::TryPlaceOnHiveSpot()
{
	AHiveSpot* Hive = FindHiveSpotInRange();
	USceneComponent* BEElderLoc = Hive->GetBEElderPlacement();
	if (!Hive || !BEElderLoc) return false;
	
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorLocation(BEElderLoc->GetComponentLocation());
	SetActorRotation(BEElderLoc->GetComponentRotation());

	UBuildSubsystem* BuildSubsystem = GetWorld()->GetSubsystem<UBuildSubsystem>();
	BuildSubsystem->StartBuild(this);
	
	return true;
}

bool ABEElder::TraceToGround(FHitResult& OutHit)
{
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 1000);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility, Params);
	return bHit && OutHit.GetActor()->ActorHasTag("Ground");
}

AHiveSpot* ABEElder::FindHiveSpotInRange()
{
	TArray<AActor*> HiveSpots;
	GetOverlappingActors(HiveSpots, AHiveSpot::StaticClass());
	for (AActor* Actor : HiveSpots)
	{
		if (AHiveSpot* HiveSpot = Cast<AHiveSpot>(Actor))
		{
			return HiveSpot;
		}
	}
	return nullptr;
}


void ABEElder::Tick(float DeltaTime)
{
	DrawDebugSphere(
	GetWorld(),
	GetActorLocation(),            // środek sfery
	SphereCollision->GetScaledSphereRadius(),          // promień
	12,                            // ilość segmentów (im więcej, tym gładsza kula)
	FColor::Green,                 // kolor
	false,                         // trwała?
	0.3f                           // czas widoczności (sekundy)
);
}
