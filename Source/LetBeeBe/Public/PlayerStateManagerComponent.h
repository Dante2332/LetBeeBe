// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStateManagerComponent.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Default UMETA(DisplayName = "Default"),
	Carrying UMETA(DisplayName = "Carrying"),
	Aiming UMETA(DisplayName = "Aiming"),
	Reloading UMETA(DisplayName = "Reloading"),
	Repairing UMETA(DisplayName = "Repairing")
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETBEEBE_API UPlayerStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStateManagerComponent();

	UPROPERTY(BlueprintReadOnly)
	EPlayerState CurrentState;

	void SetState(EPlayerState NewState);
	EPlayerState GetState() const {return CurrentState;}

	bool CanShoot() const;
	bool CanJump() const;
	bool CanPlaceBeelder() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
		
};
