// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MouseMenuController.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AC_MouseMenuController::AC_MouseMenuController() {

}
void AC_MouseMenuController::Tick(float DeltaSeconds)
{
}

void AC_MouseMenuController::BeginPlay()
{
	Super::BeginPlay();
	// Menu Widget setup
	MenuWidget = CreateWidget(this, MenuWidgetClass);
	if (!MenuWidget) {
		UE_LOG(LogTemp, Error, TEXT("MenuWidget not found!"));
		return;
	}
	MenuWidget->AddToViewport();
	PlayButton = Cast<UButton>(MenuWidget->GetWidgetFromName("Play_Button"));
	if (!PlayButton) {
		UE_LOG(LogTemp, Error, TEXT("Play button not found!"));
		return;
	}
	PlayButton->OnClicked.AddDynamic(this, &AC_MouseMenuController::PlayButtonOnClick);
	ExitButton = Cast<UButton>(MenuWidget->GetWidgetFromName("Exit_Button_2"));
	if (!ExitButton) {
		UE_LOG(LogTemp, Error, TEXT("Exit button not found!"));
		return;
	}
	ExitButton->OnClicked.AddDynamic(this, &AC_MouseMenuController::ExitButtonOnClick);
	ControlsButton = Cast<UButton>(MenuWidget->GetWidgetFromName("Controls_Button"));
	if (!ControlsButton) {
		UE_LOG(LogTemp, Error, TEXT("Controls button not found!"));
		return;
	}
	ControlsButton->OnClicked.AddDynamic(this, &AC_MouseMenuController::ControlsButtonOnClick);
	// Controls widget setup
	ControlsWidget = CreateWidget(this, ControlsWidgetClass);
	if (!ControlsWidget) {
		UE_LOG(LogTemp, Error, TEXT("ControlsWidget not found!"));
		return;
	}
	BackButton = Cast<UButton>(ControlsWidget->GetWidgetFromName("Button_1"));
	if (!BackButton) {
		UE_LOG(LogTemp, Error, TEXT("Back button not found!"));
		return;
	}
	BackButton->OnClicked.AddDynamic(this, &AC_MouseMenuController::BackButtonOnClick);
}

void AC_MouseMenuController::BackButtonOnClick()
{
	MenuWidget->AddToViewport();
	ControlsWidget->RemoveFromViewport();
}

void AC_MouseMenuController::PlayButtonOnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Click"));
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}

void AC_MouseMenuController::ExitButtonOnClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),this,EQuitPreference::Quit,true);
}

void AC_MouseMenuController::ControlsButtonOnClick()
{
	MenuWidget->RemoveFromViewport();
	ControlsWidget->AddToViewport();
}
