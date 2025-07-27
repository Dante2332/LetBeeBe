// Fill out your copyright notice in the Description page of Project Settings.
#include "InteractionComponent.h"
#include "InteractionInterface.h"
#include "LetBeeBe/LetBeeBeCharacter.h"
#include "PlayerHUD.h"
#include "PlayerWidget.h"
#include "Kismet/GameplayStatics.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Co 0.1s sprawdzaj co jest przed graczem
	GetWorld()->GetTimerManager().SetTimer(InteractionCheckHandle, this, &UInteractionComponent::CheckForInteraction, 0.1f, true);
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::CheckForInteraction()
{
	if (!bCanInteract) return;
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	AController* PlayerController = OwnerPawn->GetController();
	FVector CamLocation;
	FRotator CamRotation;
	PlayerController->GetPlayerViewPoint(CamLocation, CamRotation);

	// Przesunięcie startu nieco w przód gracza
	FVector TraceStart = OwnerPawn->GetActorLocation() + OwnerPawn->GetActorForwardVector() * 50.f;
	FVector TraceEnd = CamLocation + CamRotation.Vector() * 500.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerPawn);
	
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 0.25, 0.25, 0.25);
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, Params))
	{
		DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		AActor* HitActor = Hit.GetActor();

		if (HitActor && HitActor->Implements<UInteractionInterface>())
		{
			IInteractionInterface* Interface = Cast<IInteractionInterface>(HitActor);
			if (Interface && Interface->GetCanInteract())
			{
				if (CurrentInteractable != HitActor)
				{
					CurrentInteractable = HitActor;
					ShowPromptOnHUD(Interface->GetInteractionText());
				}
				return;
			}
		}
	}

	// Jeśli nie trafiono nic nowego
	if (CurrentInteractable)
	{
		CurrentInteractable = nullptr;
		HidePromptOnHUD();
	}
}

void UInteractionComponent::Interact()
{
	if (CurrentInteractable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("HitActor: %s"), *CurrentInteractable->GetName()));
		IInteractionInterface::Execute_HandleInteract(CurrentInteractable, GetOwner());
		HidePromptOnHUD();
	}
}

void UInteractionComponent::ShowPromptOnHUD(const FText& Prompt)
{
	if (ALetBeeBeCharacter* Player = Cast<ALetBeeBeCharacter>(GetOwner()))
	{
		if (APlayerHUD* HUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
		{
			if (UPlayerWidget* Widget = HUD->GetPlayerWidget())
			{
				Widget->ShowInteractionUI(Prompt);
			}
		}
	}
}

void UInteractionComponent::HidePromptOnHUD()
{
	if (ALetBeeBeCharacter* Player = Cast<ALetBeeBeCharacter>(GetOwner()))
	{
		if (APlayerHUD* HUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
		{
			if (UPlayerWidget* Widget = HUD->GetPlayerWidget())
			{
				Widget->HideInteractionUI();
			}
		}
	}
}

