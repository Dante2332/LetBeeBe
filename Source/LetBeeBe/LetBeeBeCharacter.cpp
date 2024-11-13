// Copyright Epic Games, Inc. All Rights Reserved.

#include "LetBeeBeCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


ALetBeeBeCharacter::ALetBeeBeCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = StartCameraBoomLength; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	Sensitivity = 0.5f;

	
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	// Set start Walk Speed
	StartWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;


	//Curve Path
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Script/Engine.CurveFloat'/Game/ThirdPerson/NewCurveBase.NewCurveBase'"));
	if (Curve.Succeeded()) 
	{
		CameraZoomCurve = Curve.Object;
	}
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ALetBeeBeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	if (CameraZoomCurve)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("HandleCameraZoomProgress"));
		CameraZoomTimeline.AddInterpFloat(CameraZoomCurve, TimelineProgress);
		CameraZoomTimeline.SetLooping(false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	}
	// Get player controller reference
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

	//Get player HUD reference
		PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
}

void ALetBeeBeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraZoomTimeline.TickTimeline(DeltaTime);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALetBeeBeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALetBeeBeCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALetBeeBeCharacter::Look);

		// Aiming
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ALetBeeBeCharacter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ALetBeeBeCharacter::StopAiming);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ALetBeeBeCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ALetBeeBeCharacter::StopSprinting);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ALetBeeBeCharacter::Shoot);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALetBeeBeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(1, 15, FColor::Yellow, TEXT("A"));
	if (Controller != nullptr)
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.0f;

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);//Enhanced Input Functions
	}
}
void ALetBeeBeCharacter::Sprint(const FInputActionValue& Value)
{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
}



void ALetBeeBeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.0f;
		AddControllerYawInput(LookAxisVector.X * Sensitivity);
		if (CameraBoom->GetTargetRotation().Pitch > 310 || CameraBoom->GetTargetRotation().Pitch < 30)
		{
			AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		if (CameraBoom->GetTargetRotation().Pitch < 310 && CameraBoom->GetTargetRotation().Pitch > 290 && LookAxisVector.Y < 0)
		{
			AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		if (CameraBoom->GetTargetRotation().Pitch < 60 && CameraBoom->GetTargetRotation().Pitch > 30 && LookAxisVector.Y > 0)
		{
			AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
		}
		SetActorRotation(Rotation);
	}
}

	void ALetBeeBeCharacter::StopSprinting(const FInputActionValue & Value)
	{
		GetCharacterMovement()->MaxWalkSpeed = StartWalkSpeed;
	}

	void ALetBeeBeCharacter::Aim(const FInputActionValue & Value)
	{
		CameraZoomTimeline.Play();
	}

	void ALetBeeBeCharacter::StopAiming(const FInputActionValue & Value)
	{
		CameraZoomTimeline.Reverse();
	}

	void ALetBeeBeCharacter::Shoot(const FInputActionValue & Value)
	{
		;
	}

	void ALetBeeBeCharacter::StopShooting(const FInputActionValue & Value)
	{
		;
	}

	

	void ALetBeeBeCharacter::HandleCameraZoomProgress(float Value)
	{
		CameraBoom->TargetArmLength = FMath::Lerp(StartCameraBoomLength, AimingCameraBoomLength, Value);
		PlayerHUD->CrosshairGap = FMath::Lerp(PlayerHUD->StartCrosshairGap, PlayerHUD->AimingCrosshairGap, Value);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CrosshairGap: %f"), PlayerHUD->CrosshairGap));
	}

