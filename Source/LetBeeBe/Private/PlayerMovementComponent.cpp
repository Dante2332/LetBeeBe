// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMovementComponent.h"
#include "LetBeeBe/LetBeeBeCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/Timelinecomponent.h"
#include "Engine/DamageEvents.h"

class AGun;
UPlayerMovementComponent::UPlayerMovementComponent()
{
	JumpZVelocity = 650.f;
	AirControl = 0.35f;
	MaxWalkSpeed = 300.f;
	MinAnalogWalkSpeed = 20.f;
	BrakingDecelerationWalking = 2000.f;
	BrakingDecelerationFalling = 1500.0f;
	StartWalkSpeed = MaxWalkSpeed;
	bOrientRotationToMovement = true; // Character moves in the direction of input...	
	RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	
	Owner = Cast<ALetBeeBeCharacter>(GetOwner());
	CameraZoomTimeline = new FTimeline();

	//Curve Path
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Script/Engine.CurveFloat'/Game/ThirdPerson/NewCurveBase.NewCurveBase'"));
	if (Curve.Succeeded()) 
	{
		CameraZoomCurve = Curve.Object;
	}
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	StartCameraBoomLength = Owner->GetCameraBoom()->TargetArmLength;
	PlayerController = Cast<APlayerController>(GetController());
	UPlayerMovementComponent::SetupPlayerInputComponent(CharacterOwner->InputComponent);
	BindCameraZoomCurve();

}

void UPlayerMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CameraZoomTimeline->TickTimeline(DeltaTime);
}


void UPlayerMovementComponent::HandleCameraZoomProgress(const float Value) const
{
	Owner->GetCameraBoom()->TargetArmLength = FMath::Lerp(StartCameraBoomLength, AimingCameraBoomLength, Value);
	APlayerHUD* PlayerHUD = Owner->GetPlayerHUD();
	PlayerHUD->CrosshairGap = FMath::Lerp(PlayerHUD->StartCrosshairGap, PlayerHUD->AimingCrosshairGap, Value);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CrosshairGap: %f"), PlayerHUD->CrosshairGap));
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
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Owner->InputComponent)) {
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
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &UPlayerMovementComponent::StopSprinting);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &UPlayerMovementComponent::Shoot);

	
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
		CharacterOwner->AddMovementInput(ForwardDirection, MovementVector.Y);//Enhanced Input Functions
		CharacterOwner->AddMovementInput(RightDirection, MovementVector.X);
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
void UPlayerMovementComponent::Sprint(const FInputActionValue& Value)
{
		MaxWalkSpeed = 600.f;
}

void UPlayerMovementComponent::StopSprinting(const FInputActionValue & Value)
{
	MaxWalkSpeed = StartWalkSpeed;
}

void UPlayerMovementComponent::Aim(const FInputActionValue & Value)
{
	CameraZoomTimeline->Play();
}

void UPlayerMovementComponent::StopAiming(const FInputActionValue & Value)
{
	CameraZoomTimeline->Reverse();
}

void UPlayerMovementComponent::Shoot(const FInputActionValue & Value)
{
	if (OnShoot.IsBound())
	{
		OnShoot.Broadcast();
	}
	FHitResult HitResult;
	FVector Start = Owner->GetFollowCamera()->GetRelativeLocation();
	FVector End = Start + Owner->GetFollowCamera()->GetForwardVector() * 500;
	if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel2))
	{
		HitResult.GetActor()->OnTakePointDamage;
	}
}

void UPlayerMovementComponent::StopShooting(const FInputActionValue & Value)
{
	;
}
void UPlayerMovementComponent::BindCameraZoomCurve()
{
	if (CameraZoomCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("HandleCameraZoomProgress"));
		CameraZoomTimeline->AddInterpFloat(CameraZoomCurve, TimelineProgress);
		CameraZoomTimeline->SetLooping(false);
	}
	else
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CameraZoomCurve Not Found"));
	}
}
//Destructor
UPlayerMovementComponent::~UPlayerMovementComponent()
{
	if (CameraZoomTimeline)
	{
		delete CameraZoomTimeline;
		CameraZoomTimeline = nullptr;
	}
}

