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
#include "Components/Timelinecomponent.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//Constructor
ALetBeeBeCharacter::ALetBeeBeCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	// Configure character movement
	
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	// The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarriedWeapon"));
	Weapon->SetupAttachment(GetMesh(),("hand_r"));
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm
	



	
}

void ALetBeeBeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	// Get player controller reference
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

	//Get player HUD reference
		PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
}

void ALetBeeBeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

