// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AProceduralShooterGameModeBase::AProceduralShooterGameModeBase() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}
void AProceduralShooterGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
