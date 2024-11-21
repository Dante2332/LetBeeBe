// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{;
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,AController* instigator, AActor* DamageCauser)
{
	float HealthChange = FMath::Min(Damage, CurrentHealth);
	CurrentHealth -= HealthChange;
	OnComponentDamaged.Broadcast(instigator, Damage, CurrentHealth);
	if(CurrentHealth <= 0.f)
	{
		OnComponentDead.Broadcast(instigator);
		
	}
} 