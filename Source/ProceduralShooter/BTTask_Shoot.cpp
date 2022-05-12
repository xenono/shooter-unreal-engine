// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "C_BaseCharacter.h"
#include "C_Gun.h"

UBTTask_Shoot::UBTTask_Shoot() {
    NodeName = TEXT("Shoot");
}
EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{   
    Super::ExecuteTask(OwnerComp, NodeMemory);
	if (!OwnerComp.GetAIOwner()) {
		UE_LOG(LogTemp, Error, TEXT("Owner AI component not found in BTTask_Shoot"));
		return EBTNodeResult::Failed;
	}
	AC_BaseCharacter* Character = Cast<AC_BaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character) {
		UE_LOG(LogTemp, Error, TEXT("Character pawn not found in BTTask_Shoot"));
		return EBTNodeResult::Failed;
	}
	Character->Shoot();
	if (Character->GetBulletsInMagazine() == 0)
		Character->GetGun()->Reload();
    return EBTNodeResult::Succeeded;
}
