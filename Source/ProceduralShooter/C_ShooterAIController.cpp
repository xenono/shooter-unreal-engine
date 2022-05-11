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
	AC_BaseCharacter* xd = Cast<AC_BaseCharacter>(GetPawn());
	//UE_LOG(LogTemp, Warning, TEXT("%f"), xd->CurrentMovementType);
}