// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "MaterialHLSLTree.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"   
#include "Components/TimelineComponent.h"
#include "LetBeeBe/LetBeeBeCharacter.h"

APlayerHUD::APlayerHUD()
{
	CameraZoomTimeline = new FTimeline();      
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Script/Engine.CurveFloat'/Game/ThirdPerson/NewCurveBase.NewCurveBase'"));
	if (Curve.Succeeded())                                                                                                                      
	{                                                                                                                                           
		CameraZoomCurve = Curve.Object;                                                                                                         
	}                                                                 
}
void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	BindCameraZoomCurve();
	BindAimHandle();
}


void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();
	if (Canvas)
	{
		// Get screen center
		const float CenterX = Canvas->ClipX / 2.0f;
		const float CenterY = Canvas->ClipY / 2.0f;

		// Set crosshair lines length
		const float LineLength = 10.f;

		FLinearColor CrosshairColor = FLinearColor::White;

		DrawLine(CenterX - CrosshairGap - LineLength, CenterY, CenterX - CrosshairGap, CenterY, CrosshairColor);
		DrawLine(CenterX + CrosshairGap, CenterY, CenterX + CrosshairGap + LineLength, CenterY, CrosshairColor);
		DrawLine(CenterX, CenterY - CrosshairGap - LineLength, CenterX, CenterY - CrosshairGap, CrosshairColor);
		DrawLine(CenterX, CenterY + CrosshairGap, CenterX, CenterY + CrosshairGap + LineLength , CrosshairColor);
	}
}
void APlayerHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraZoomTimeline->TickTimeline(DeltaTime); 
}

void APlayerHUD::HandleCameraZoomProgress(const float Value)
{
	ALetBeeBeCharacter* PlayerCharacter = GetPlayerCharacter();
	PlayerCharacter->GetCameraBoom()->TargetArmLength = FMath::Lerp(PlayerCharacter->GetStartCameraBoomLength(), PlayerCharacter->GetAimingCameraBoomLength(), Value);    
	CrosshairGap = FMath::Lerp(StartCrosshairGap, AimingCrosshairGap, Value);
}

ALetBeeBeCharacter* APlayerHUD::GetPlayerCharacter() const
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		ALetBeeBeCharacter* PlayerCharacter = Cast<ALetBeeBeCharacter>(PlayerController->GetPawn());
		return PlayerCharacter;
	}
	return nullptr;
}

void APlayerHUD::BindCameraZoomCurve()
{
	if (CameraZoomCurve)                                                                                                             
	{                                                                                                                                
		FOnTimelineFloat TimelineProgress;                                                                                           
		TimelineProgress.BindUFunction(this, FName("HandleCameraZoomProgress"));                                                     
		CameraZoomTimeline->AddInterpFloat(CameraZoomCurve, TimelineProgress);                                                       
		CameraZoomTimeline->SetLooping(false);                                                                                       
	}                                                                                                                                
	else                                                                                                                             
	{                                                                                                                                
		                                                                                                                             
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CameraZoomCurve Not Found"));                              
	}                                                                                                                                
}

void APlayerHUD::BindAimHandle()
{
	if (const ALetBeeBeCharacter* Player = GetPlayerCharacter())
	{
		UPlayerMovementComponent* PlayerMovement = Cast<UPlayerMovementComponent>(Player->GetMovementComponent());
		PlayerMovement->OnAim.BindUObject(this, &APlayerHUD::AimHandle);
	}
}

void APlayerHUD::AimHandle(bool bIsAiming)
{
	if (bIsAiming)
	{
		CameraZoomTimeline->Play();
	}
	else
	{
		CameraZoomTimeline->Reverse();
	}
}


APlayerHUD::~APlayerHUD()
{
	if (CameraZoomTimeline)
	{
		delete CameraZoomTimeline;
		CameraZoomTimeline = nullptr;
	}
}
