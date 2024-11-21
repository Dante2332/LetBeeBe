// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerHUD.h"
#include "Logging/LogMacros.h"
#include "LetBeeBeCharacter.generated.h"
class AGun;
class UHealthComponent;
class USpringArmComponent;
class UCameraComponent;
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

	//Health Component
	UPROPERTY(VisibleAnywhere, Category = Health, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AGun> WeaponClass;
	
	UPROPERTY()
	AGun* Weapon;	
	
	UPROPERTY()
	APlayerHUD* PlayerHUD;

	void SpawnWeapon();

public:
	ALetBeeBeCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE class APlayerHUD* GetPlayerHUD() const { return PlayerHUD; }
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:

	
	// To add mapping context
	virtual void BeginPlay();
	
	virtual void Tick(float DeltaTime);


};


