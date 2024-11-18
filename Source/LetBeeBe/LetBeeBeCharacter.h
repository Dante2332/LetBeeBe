// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerHUD.h"
#include "Logging/LogMacros.h"
#include "LetBeeBeCharacter.generated.h"

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

	/** WeaponMesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Weapon;
	

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	APlayerHUD* PlayerHUD;




	

public:
	ALetBeeBeCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE class APlayerHUD* GetPlayerHUD() const { return PlayerHUD; }
protected:

	
	// To add mapping context
	virtual void BeginPlay();
	
	virtual void Tick(float DeltaTime);


};


