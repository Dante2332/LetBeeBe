// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerHUD.h"
#include "Logging/LogMacros.h"
#include "LetBeeBeCharacter.generated.h"
class UWeaponManager;
class AGun;
class UHealthComponent;
class USpringArmComponent;
class UCameraComponent;
class UInteractionComponent;
class UPlayerStateManagerComponent;
struct FTimeline;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ALetBeeBeCharacter : public ACharacter
{	
	GENERATED_BODY()
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
		
	float StartCameraBoomLength;

	float AimingCameraBoomLength = 250.f;

	//Health Component
	UPROPERTY(VisibleAnywhere, Category = Health, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY()
	APlayerHUD* PlayerHUD;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UWeaponManager* WeaponManager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* BeelderAttachment;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPlayerStateManagerComponent* PlayerStateManager;
public:
	ALetBeeBeCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE class APlayerHUD* GetPlayerHUD() const { return PlayerHUD; }
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }
	FORCEINLINE class UWeaponManager* GetWeaponManager() const { return WeaponManager; }
	FORCEINLINE float GetStartCameraBoomLength() const { return StartCameraBoomLength; }
	FORCEINLINE float GetAimingCameraBoomLength() const { return AimingCameraBoomLength; }
	FORCEINLINE class USceneComponent* GetBeelderAttachment() const { return BeelderAttachment; }


protected:

	
	// To add mapping context
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;


};


