// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManager.generated.h"


class AGun;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LETBEEBE_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE AGun* GetEquippedWeapon() const { return EquippedWeapon; }
	FORCEINLINE AGun* GetHiddenWeapon() const { return HiddenWeapon; }
    void SpawnWeapon(const TSubclassOf<AGun>& WeaponToSpawn);
	void EquipWeapon(AGun* WeaponToEquip);
	void BuyWeapon(const TSubclassOf<AGun>& WeaponToBuy);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AGun> PrimaryWeaponClass;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AGun> SecondaryWeaponClass;
	UPROPERTY()
	AGun* PrimaryWeapon;
	UPROPERTY()
	AGun* SecondaryWeapon;
	UPROPERTY()
	AGun* HiddenWeapon;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AGun* EquippedWeapon;
	void BindWeaponSwitchHandle();
	void SwitchWeapon(int32 WeaponIndex);
	bool CanBuyWeapon() const;
};


