// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StopAiming.h"
#include "AIController.h"
#include "C_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_StopAiming::UBTTask_StopAiming() {
	NodeName = TEXT("Stop Aiming");
}
EBTNodeResult::Type UBTTask_StopAiming::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	Character->GetCharacterMovement()->MaxWalkSpeed = 600;
	Character->StopAiming();
	UE_LOG(LogTemp, Warning, TEXT("%i"), Character->CurrentMovementType);
	return EBTNodeResult::Succeeded;
}
