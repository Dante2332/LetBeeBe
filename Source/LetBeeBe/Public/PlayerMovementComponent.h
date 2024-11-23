// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShotSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadSignature);

class USpringArmComponent;
class ALetBeeBeCharacter;
class UInputMappingContext;
class UInputAction;
struct FTimeline;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class LETBEEBE_API UPlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UPlayerMovementComponent();
	~UPlayerMovementComponent();

	UPROPERTY(BlueprintAssignable)
	FShotSignature OnShoot;
	UPROPERTY(BlueprintAssignable)
	FReloadSignature OnReload;	

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	APlayerController* PlayerController;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
private:
	ALetBeeBeCharacter* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float Sensitivity = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float StartWalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;


	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	/** Called for sprint input */
	void Sprint(const FInputActionValue& Value);	
	void StopSprinting(const FInputActionValue& Value);

	/** Called for aim input*/
	void Aim(const FInputActionValue& Value);
	void StopAiming(const FInputActionValue& Value);

	/** Called for shoot input*/
	void Shoot(const FInputActionValue& Value);
	
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	void Reload(const FInputActionValue& Value);
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Aim Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	/** Shoot Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;
	//Timeline for aiming
	FTimeline* CameraZoomTimeline;
	UPROPERTY(EditAnywhere, Category = Camera)
	UCurveFloat* CameraZoomCurve;
	
	UFUNCTION()
	void HandleCameraZoomProgress(const float Value) const;
	UFUNCTION()
	void BindCameraZoomCurve();
	float StartCameraBoomLength;

	float AimingCameraBoomLength = 250.f;
};
