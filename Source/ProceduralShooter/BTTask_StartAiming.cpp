// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StartAiming.h"
#include "AIController.h"
#include "C_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_StartAiming::UBTTask_StartAiming() {
	NodeName = TEXT("Start Aiming");
}
EBTNodeResult::Type UBTTask_StartAiming::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (!OwnerComp.GetAIOwner()) {
		UE_LOG(LogTemp, Error, TEXT("Owner AI component not found in BTTask_StartAiming"));
		return EBTNodeResult::Failed;
	}
	AC_BaseCharacter* Character = Cast<AC_BaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character) {
		UE_LOG(LogTemp, Error, TEXT("Character pawn not found in BTTask_StartAiming"));
		return EBTNodeResult::Failed;
	}
	Character->GetCharacterMovement()->MaxWalkSpeed = 300;
	Character->StartAiming();
	return EBTNodeResult::Succeeded;
}
