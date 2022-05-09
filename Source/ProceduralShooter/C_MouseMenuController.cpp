// Fill out your copyright notice in the Description page of Project Settings.


#include "C_MouseMenuController.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

AC_MouseMenuController::AC_MouseMenuController() {

}
void AC_MouseMenuController::Tick(float DeltaSeconds)
{
}

void AC_MouseMenuController::BeginPlay()
{
	Super::BeginPlay();
	MenuWidget = CreateWidget(this, MenuWidgetClass);
	if (!MenuWidget) {
		UE_LOG(LogTemp, Error, TEXT("MenuWidget not found!"));
		return;
	}
	MenuWidget->AddToViewport();
	PlayButton = Cast<UButton>(MenuWidget->GetWidgetFromName("Play_Button"));
	if (!PlayButton) {
		UE_LOG(LogTemp, Error, TEXT("Play button not found!"));
	}
	PlayButton->OnClicked.AddDynamic(this, &AC_MouseMenuController::PlayButtonOnClick);
}

void AC_MouseMenuController::PlayButtonOnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("Click"));
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}
