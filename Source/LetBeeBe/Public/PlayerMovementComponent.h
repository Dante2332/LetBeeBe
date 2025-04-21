// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "PlayerMovementComponent.generated.h"

DECLARE_DELEGATE_OneParam(FAimSignature, bool bIsAiming);
DECLARE_DELEGATE_OneParam(FShotSignature, bool bShouldShoot);
DECLARE_DELEGATE(FReloadSignature);
DECLARE_DELEGATE_OneParam(FWeaponSwitchSignature, int32 WeaponIndex);
DECLARE_MULTICAST_DELEGATE_OneParam(FInteractSignature, AActor* Interactor);

class USpringArmComponent;
class ALetBeeBeCharacter;
class UInputAction;

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

	
	FAimSignature OnAim;
	FShotSignature OnShoot;
	FReloadSignature OnReload;
	FWeaponSwitchSignature OnWeaponSwitch;
	FInteractSignature OnInteract;

protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	APlayerController* PlayerController;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
private:
	bool bIsMovingForward;
	bool bIsSprinting;
	bool bIsAiming;
	
	UPROPERTY()
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
	void StartSprinting();	
	void StopSprinting();

	/** Called for aim input*/
	void Aim();
	void StopAiming();

	/** Called for shoot input*/
	void StartShooting();
	void StopShooting();
	
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	void Reload();

	void SwitchWeapon(const FInputActionValue& Value);

	void Interact();
	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	
};
