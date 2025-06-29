// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HiveSpot.generated.h"

class USphereComponent;

UCLASS()
class LETBEEBE_API AHiveSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHiveSpot();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE USceneComponent* GetBEElderPlacement() const { return BEElderPlacement; }
private:
	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BEElderPlacement;

};
