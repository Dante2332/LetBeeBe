// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"
#include "LetBeeBe/LetBeeBeCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"


UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	StartWalkSpeed = MaxWalkSpeed;
	OwnerCharacter = Cast<ALetBeeBeCharacter>(GetOwner());
	if (OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Movement Component"));
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Found"));
	}
	
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	UPlayerMovementComponent::SetupPlayerInputComponent(CharacterOwner->InputComponent);
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Found"));
	}
}

void UPlayerMovementComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			UE_LOG(LogTemp, Warning, TEXT("Subsystem found"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Subsystem Not Found"));
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwnerCharacter->InputComponent)) {
		UE_LOG(LogTemp, Warning, TEXT("Enhanced input component found"));
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, OwnerCharacter, &ALetBeeBeCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, OwnerCharacter, &ALetBeeBeCharacter::StopJumping);
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UPlayerMovementComponent::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UPlayerMovementComponent::Look);

		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &UPlayerMovementComponent::StopAiming);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &UPlayerMovementComponent::StopSprinting);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &UPlayerMovementComponent::Shoot);

	
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
	GEngine->AddOnScreenDebugMessage(1, 15, FColor::Yellow, TEXT("A"));
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
		CharacterOwner->AddMovementInput(ForwardDirection, MovementVector.Y);//Enhanced Input Functions
		CharacterOwner->AddMovementInput(RightDirection, MovementVector.X);
	}
}
void UPlayerMovementComponent::Sprint(const FInputActionValue& Value)
{
		MaxWalkSpeed = 600.f;
}



void UPlayerMovementComponent::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (PlayerController != nullptr)
	{
		USpringArmComponent* CameraBoom = OwnerCharacter->GetCameraBoom();
		// add yaw and pitch input to controller
		FRotator Rotation = PlayerController->GetControlRotation();
		Rotation.Pitch = 0.0f;
		PlayerController->AddYawInput(LookAxisVector.X * Sensitivity);
		if (CameraBoom->GetTargetRotation().Pitch > 310 || CameraBoom->GetTargetRotation().Pitch < 30)
		{
			CharacterOwner->AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		if (CameraBoom->GetTargetRotation().Pitch < 310 && CameraBoom->GetTargetRotation().Pitch > 290 && LookAxisVector.Y < 0)
		{
			CharacterOwner->AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		if (CameraBoom->GetTargetRotation().Pitch < 60 && CameraBoom->GetTargetRotation().Pitch > 30 && LookAxisVector.Y > 0)
		{
			CharacterOwner->AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		CharacterOwner->SetActorRotation(Rotation);
	}
}

	void UPlayerMovementComponent::StopSprinting(const FInputActionValue & Value)
	{
		MaxWalkSpeed = StartWalkSpeed;
	}

	void UPlayerMovementComponent::Aim(const FInputActionValue & Value)
	{
		;
	}

	void UPlayerMovementComponent::StopAiming(const FInputActionValue & Value)
	{
	;
	}

	void UPlayerMovementComponent::Shoot(const FInputActionValue & Value)
	{
		;
	}

	void UPlayerMovementComponent::StopShooting(const FInputActionValue & Value)
	{
		;
	}

