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
	void StartAiming();
	void StopAiming();
private:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> CrosshairWidgetClass;
	UPROPERTY()
		UUserWidget* CrosshairWidget;
};
