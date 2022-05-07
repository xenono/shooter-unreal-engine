// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerController.h"
#include "Blueprint/UserWidget.h"

AC_PlayerController::AC_PlayerController() {
	PrimaryActorTick.bCanEverTick = true;

}
void AC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	CrosshairWidget = CreateWidget(this, CrosshairWidgetClass);
	if (!CrosshairWidget) {
		UE_LOG(LogTemp, Warning, TEXT("No crosshair widget"));
		return;
	}
	HealthWidget = CreateWidget(this, HealthWidgetClass);
	if (!HealthWidget) {
		UE_LOG(LogTemp, Warning, TEXT("No health widget"));
		return;
	}
	HealthWidget->AddToViewport();
}

void AC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AC_PlayerController::StartAiming);
	InputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AC_PlayerController::StopAiming);
	InputComponent->GetActionBinding(0).bConsumeInput = 0;
	InputComponent->GetActionBinding(1).bConsumeInput = 0;
}

void AC_PlayerController::StartAiming() {
	if (CrosshairWidget) {
		CrosshairWidget->AddToViewport();
	}
}

void AC_PlayerController::StopAiming() {
	if (CrosshairWidget) {
		CrosshairWidget->RemoveFromViewport();
	}
}