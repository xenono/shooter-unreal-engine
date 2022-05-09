// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_MouseMenuController.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALSHOOTER_API AC_MouseMenuController : public APlayerController
{
	GENERATED_BODY()
public:
	AC_MouseMenuController();
	virtual void Tick(float DeltaSeconds);
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void PlayButtonOnClick();
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> MenuWidgetClass;
	UPROPERTY()
		UUserWidget* MenuWidget;
	UPROPERTY()
		class UButton* PlayButton;
};
