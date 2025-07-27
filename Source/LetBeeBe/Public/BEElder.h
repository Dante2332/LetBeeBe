// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "BEElder.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeelderPlacedSignature, ABEElder*, BEElder);

class AHiveSpot;

UCLASS()
class LETBEEBE_API ABEElder : public AInteractable
{
	GENERATED_BODY()

public:
	ABEElder();
	UPROPERTY(BlueprintAssignable)
	FOnBeelderPlacedSignature OnBeelderPlaced;
	void HandleInteract_Implementation(AActor* Interactor);
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual FText GetInteractionText() const override;

	
private:
	void Pickup();
	bool Drop();
	bool CanBeDropped();
	bool TryPlaceOnGround();
	bool TryPlaceOnHiveSpot();
	bool TraceToGround(FHitResult& OutHit);
	bool bIsBuilding = false;
	class AHiveSpot* FindHiveSpotInRange();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	bool bIsPicked = false;

	UPROPERTY(EditAnywhere)
	FVector GroundDropOffset = FVector(0.f, 0.f, 30.f);

	UPROPERTY(EditAnywhere)
	float HiveSpotSearchRadius = 100.f;
};
