// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/Timelinecomponent.h"
#include "PlayerHUD.h"
#include "Logging/LogMacros.h"
#include "LetBeeBeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ALetBeeBeCharacter : public ACharacter
{
	GENERATED_BODY()
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;



	/** Timeline Setup for aim zooming */
	FTimeline CameraZoomTimeline;

	UFUNCTION()
	void HandleCameraZoomProgress(float Value);

	float StartCameraBoomLength = 400.f;

	float AimingCameraBoomLength = 250.f;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCurveFloat* CameraZoomCurve;

	APlayerHUD* PlayerHUD;
public:
	ALetBeeBeCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float StartWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float Sensitivity;
	

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for sprit input */
	void Sprint(const FInputActionValue& Value);	
	void StopSprinting(const FInputActionValue& Value);

	/** Called for aim input*/
	void Aim(const FInputActionValue& Value);
	void StopAiming(const FInputActionValue& Value);

	/** Called for shoot input*/
	void Shoot(const FInputActionValue& Value);
	void StopShooting(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:

	
	// To add mapping context
	virtual void BeginPlay();
	
	virtual void Tick(float DeltaTime);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

