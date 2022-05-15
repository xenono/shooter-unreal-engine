// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProceduralShooterGameModeBase.generated.h"


UCLASS()
class PROCEDURALSHOOTER_API AProceduralShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AProceduralShooterGameModeBase();
	virtual void Tick(float DeltaSeconds);
	void PawnKilled(APawn* KilledPawn);
	void EndGame(bool isPlayerWinner);

};
