// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "BrainComponent.h"
#include "C_ShooterAIController.h"

AProceduralShooterGameModeBase::AProceduralShooterGameModeBase() {
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}
void AProceduralShooterGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AProceduralShooterGameModeBase::PawnKilled(APawn* KilledPawn)
{
	APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
	if (PlayerController) {
		for (AAIController* AIController : TActorRange<AAIController>(GetWorld())) {
			AIController->GetBrainComponent()->StopLogic(TEXT("The End"));
		}
		EndGame(false);
	}
	for (AC_ShooterAIController* Controller : TActorRange<AC_ShooterAIController>(GetWorld())) {
		if (!Controller->IsDead()) {
			return;
		}
	}
	EndGame(true);

}

void AProceduralShooterGameModeBase::EndGame(bool isPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		bool bIsWinner = Controller->IsPlayerController() == isPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}

}
