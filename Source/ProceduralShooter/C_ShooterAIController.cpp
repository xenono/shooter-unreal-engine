// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AC_ShooterAIController::BeginPlay() {
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (AIBehavior) {
		
		RunBehaviorTree(AIBehavior);
		if (GetBlackboardComponent()) {
			UE_LOG(LogTemp, Warning, TEXT("XDD"));
			GetBlackboardComponent()->SetValueAsVector("X", FVector(-610, 920, 117));

		}
	}
}