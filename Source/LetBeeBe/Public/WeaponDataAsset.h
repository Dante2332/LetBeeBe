// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

UENUM (BlueprintType)
enum class EWeaponType : uint8
{
	Primary,
	Secondary
};

USTRUCT (BlueprintType)
struct FWeaponInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* WeaponMesh;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	bool bIsFullAuto;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	int32 TotalAmmo;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	int32 ClipSize;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	float RateOfFire;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	float ReloadSpeed;

	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	float Damage;
	
};
UCLASS()
class LETBEEBE_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY (EditAnywhere, BlueprintReadWrite)
	FWeaponInfo WeaponInfo;
};
