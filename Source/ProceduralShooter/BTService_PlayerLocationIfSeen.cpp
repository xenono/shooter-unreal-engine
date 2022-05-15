// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"


UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen() {
	NodeName = TEXT("Update player location if seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn) {
		UE_LOG(LogTemp, Error, TEXT("Player Pawn has not been  found in UBT_Service Player Location If Seen"));
		return;
	}
	if (!OwnerComp.GetAIOwner()) {
		UE_LOG(LogTemp, Error, TEXT("Owner AA Component has not been  found in UBT_Service Player Location If Seen"));
		return;
	}
	bool IsPlayerVisible = OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn);
	if (IsPlayerVisible) {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
		AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
		FVector PlayerLocation = Player->GetActorLocation();
	}
	else {
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}


}