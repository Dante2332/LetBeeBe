// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"
#include "LetBeeBe/LetBeeBeCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "PlayerStateManagerComponent.h"
#include "InteractionComponent.h"

class AGun;
UPlayerMovementComponent::UPlayerMovementComponent()
{
	JumpZVelocity = 650.f;
	AirControl = 0.35f;
	MaxWalkSpeed = 300.f;
	MinAnalogWalkSpeed = 20.f;
	BrakingDecelerationWalking = 2000.f;
	BrakingDecelerationFalling = 1500.0f;
	bOrientRotationToMovement = true; // Character moves in the direction of input...	
	RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	Owner = Cast<ALetBeeBeCharacter>(GetOwner());
	StateManager = Owner->GetPlayerStateManager();
	UPlayerMovementComponent::SetupPlayerInputComponent(Owner->InputComponent);
}

void UPlayerMovementComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, Owner, &ALetBeeBeCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, Owner, &ALetBeeBeCharacter::StopJumping);
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UPlayerMovementComponent::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UPlayerMovementComponent::Look);

		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &UPlayerMovementComponent::StopAiming);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::StartSprinting);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &UPlayerMovementComponent::StopSprinting);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::StartShooting);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &UPlayerMovementComponent::StopShooting);
		
		//Reloading
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::Reload);

		//SwitchingWeapon
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::SwitchWeapon);

		//Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void UPlayerMovementComponent::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (PlayerController)
	{
		// find out which way is forward
		FRotator Rotation = PlayerController->GetControlRotation();
		Rotation.Pitch = 0.0f;

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		// get right vector 
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		// add movement 
		Owner->AddMovementInput(ForwardDirection, MovementVector.Y);//Enhanced Input Functions
		Owner->AddMovementInput(RightDirection, MovementVector.X);
		if (MovementVector.Y > 0)
		{
			bIsMovingForward = true;
		}
		else
		{
			bIsMovingForward = false;
		}
		if (!bIsMovingForward && bIsSprinting)
		{
			StopSprinting();
		}
	}
}



void UPlayerMovementComponent::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (PlayerController != nullptr)
	{
		USpringArmComponent* CameraBoom = Owner->GetCameraBoom();
		// add yaw and pitch input to controller
		FRotator Rotation = PlayerController->GetControlRotation();
		Rotation.Pitch = 0.0f;
		PlayerController->AddYawInput(LookAxisVector.X * Sensitivity);
		if (CameraBoom->GetTargetRotation().Pitch > 310 || CameraBoom->GetTargetRotation().Pitch < 30)
		{
			Owner->AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		if (CameraBoom->GetTargetRotation().Pitch < 310 && CameraBoom->GetTargetRotation().Pitch > 290 && LookAxisVector.Y < 0)
		{
			Owner->AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		if (CameraBoom->GetTargetRotation().Pitch < 60 && CameraBoom->GetTargetRotation().Pitch > 30 && LookAxisVector.Y > 0)
		{
			Owner->AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		Owner->SetActorRotation(Rotation);
	}
}
void UPlayerMovementComponent::StartSprinting()
{
	if (bIsAiming)
	{
		StopAiming();
	}
	bIsSprinting = true;
	StartWalkSpeed = MaxWalkSpeed;
	MaxWalkSpeed *= 2;
}

void UPlayerMovementComponent::StopSprinting()
{
	bIsSprinting = false;
	MaxWalkSpeed = StartWalkSpeed;
}

void UPlayerMovementComponent::Aim()
{
	if (StateManager->GetState() != EPlayerState::Default) return; 
	if (OnAim.IsBound())
	{
		if (bIsSprinting)
		{
			StopSprinting();
		}
		OnAim.Execute(true);
		bIsAiming = true;
		
	}
}

void UPlayerMovementComponent::StopAiming()
{
	if (OnAim.IsBound())
	{
		OnAim.Execute(false);
		bIsAiming = false;
	}
}

void UPlayerMovementComponent::StartShooting()
{
	if (StateManager->GetState() != EPlayerState::Carrying)
	{
		if (OnShoot.IsBound())
		{
			OnShoot.Execute(true);
		}
	}
	else
	{
		if (UInteractionComponent* InteractionComponent = Owner->FindComponentByClass<UInteractionComponent>())
		{
			InteractionComponent->Interact();
		}
	}
	
}

void UPlayerMovementComponent::StopShooting()
{
	if (OnShoot.IsBound())
	{
		OnShoot.Execute(false);
	}
}


void UPlayerMovementComponent::Reload()
{
	if (OnReload.IsBound())
	{
		OnReload.Execute();
	}
}

void UPlayerMovementComponent::SwitchWeapon(const FInputActionValue& Value)
{
	if (OnWeaponSwitch.IsBound())
	{
		int32 WeaponSlot = FMath::RoundToInt32(Value.Get<float>());	
		OnWeaponSwitch.Execute(WeaponSlot);
	}
}

void UPlayerMovementComponent::Interact()
{
	if (UInteractionComponent* InteractionComponent = Owner->FindComponentByClass<UInteractionComponent>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("F")));
		InteractionComponent->Interact();
	}
}



