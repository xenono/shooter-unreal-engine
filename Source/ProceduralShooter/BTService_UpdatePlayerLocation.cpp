// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation() {
	NodeName = TEXT("Update player location");
}
void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (!PlayerPawn) {
		UE_LOG(LogTemp, Error, TEXT("Player Pawn has not been  found in UBT_Service Update Player Location"));
		return;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	//UE_LOG(LogTemp,Warning, TEXT("%f %f %f"), OwnerComp.GetBlackboardComponent()->GetValueAsVector("Player").X, OwnerComp.GetBlackboardComponent()->GetValueAsVector("Player").Y, OwnerComp.GetBlackboardComponent()->GetValueAsVector("Player").Z)
}