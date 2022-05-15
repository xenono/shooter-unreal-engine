// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "C_BaseCharacter.h"

void AC_ShooterAIController::BeginPlay() {
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
	}
	
}

void AC_ShooterAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

bool AC_ShooterAIController::IsDead() {
	AC_BaseCharacter* ControlledCharacter = Cast<AC_BaseCharacter>(GetPawn());
	if (ControlledCharacter) {
		return ControlledCharacter->IsDead();
	}
	return true;
}