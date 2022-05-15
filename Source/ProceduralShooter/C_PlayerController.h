// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerController.generated.h"

UCLASS()
class PROCEDURALSHOOTER_API AC_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AC_PlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	void StartAiming();
	void StopAiming();
	void RedirectToMenu();
private:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> CrosshairWidgetClass;
	UPROPERTY()
		UUserWidget* CrosshairWidget;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HealthWidgetClass;
	UPROPERTY()
		UUserWidget* HealthWidget;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenWidgetClass;
	UPROPERTY()
		UUserWidget* WinScreenWidget;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenWidgetClass;
	UPROPERTY()
		UUserWidget* LoseScreenWidget;
	UPROPERTY(EditAnywhere)
		float RestartDelay = 5.f;
	FTimerHandle RestartTimer;
};
