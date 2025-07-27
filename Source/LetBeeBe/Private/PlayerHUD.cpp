// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "BuildSubsystem.h"
#include "MaterialHLSLTree.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerStateManagerComponent.h"
#include "PlayerWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "LetBeeBe/LetBeeBeCharacter.h"
#include "CrosshairUI.h"
#include "BuildUI.h"

APlayerHUD::APlayerHUD()
{
	CameraZoomTimeline = new FTimeline();      
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Script/Engine.CurveFloat'/Game/ThirdPerson/NewCurveBase.NewCurveBase'"));
	if (Curve.Succeeded())                                                                                                                      
	{                                                                                                                                           
		CameraZoomCurve = Curve.Object;                                                                                                         
	}
	static ConstructorHelpers::FClassFinder<UPlayerWidget> BPPlayerWidgetClass(TEXT("/Game/ThirdPerson/UI/WBP_PlayerWidget"));
	PlayerWidgetClass = BPPlayerWidgetClass.Class;
}
void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
	PlayerWidget->AddToViewport();	
	PlayerWidget->GetCrosshairUI()->SetCrosshairGap(StartCrosshairGap);
	BindCameraZoomCurve();
	BindAimHandle();
	BindHandleBuildStart();
	BindHandleBuildEnd();
}



void APlayerHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraZoomTimeline->TickTimeline(DeltaTime);
}

void APlayerHUD::HandleCameraZoomProgress(const float Value)
{
	if (PlayerWidget && PlayerWidget->GetCrosshairUI())
	{
		ALetBeeBeCharacter* PlayerCharacter = GetPlayerCharacter();
		PlayerCharacter->GetCameraBoom()->TargetArmLength = FMath::Lerp(PlayerCharacter->GetStartCameraBoomLength(), PlayerCharacter->GetAimingCameraBoomLength(), Value);
		float Gap = FMath::Lerp(StartCrosshairGap, AimCrosshairGap, Value); // możesz trzymać w UPlayerWidget jeśli chcesz
		PlayerWidget->GetCrosshairUI()->SetCrosshairGap(Gap);
	}
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

UPlayerWidget* APlayerHUD::GetPlayerWidget() const
{
	return PlayerWidget;
}

void APlayerHUD::ShowBuildUI()
{
	PlayerWidget->GetBuildUI()->SetVisibility(ESlateVisibility::Visible);
}

void APlayerHUD::HideBuildUI()
{
	PlayerWidget->GetBuildUI()->SetVisibility(ESlateVisibility::Hidden);
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
	UPlayerStateManagerComponent* PlayerStateManager = GetPlayerCharacter()->GetPlayerStateManager();
	if (bIsAiming && PlayerStateManager->GetState() == EPlayerState::Default)
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
void APlayerHUD::BindHandleBuildStart()
{
	UBuildSubsystem* BuildSubsystem = GetWorld()->GetSubsystem<UBuildSubsystem>();
	BuildSubsystem->OnBuildStart.AddDynamic(this, &APlayerHUD::APlayerHUD::HandleBuildStart);
}
void APlayerHUD::HandleBuildStart()
{
	ShowBuildUI();
}
void APlayerHUD::BindHandleBuildEnd()
{
	UBuildSubsystem* BuildSubsystem = GetWorld()->GetSubsystem<UBuildSubsystem>();
	BuildSubsystem->OnBuildEnd.AddDynamic(this, &APlayerHUD::HandleBuildEnd);
}

void APlayerHUD::HandleBuildEnd()
{
	HideBuildUI();
}