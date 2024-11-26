// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "PlayerMovementComponent.generated.h"

DECLARE_DELEGATE_OneParam(FAimSignature, bool bIsAiming);
DECLARE_DELEGATE(FShotSignature);
DECLARE_DELEGATE(FReloadSignature);

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

protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	APlayerController* PlayerController;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
private:
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

};
