// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProceduralShooterGameModeMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALSHOOTER_API AProceduralShooterGameModeMenu : public AGameModeBase
{
	GENERATED_BODY()
public:
	AProceduralShooterGameModeMenu();
	virtual void Tick(float DeltaSeconds);
	virtual void BeginPlay() override;
};
