// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyRobotController.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALSHOOTER_API AEnemyRobotController : public AAIController
{
	GENERATED_BODY()

		UBehaviorTreeComponent* BehaviorComp;

		UBlackboardComponent* BlackboardComp;

		UPROPERTY(EditDefaultsOnly, Category = AI)
			FName LocationToGoKey;
		
		UPROPERTY(EditDefaultsOnly, Category = AI)
			FName PlayerKey;

		TArray<AActor*> PatrolPoints;	

public:
	AEnemyRobotController();	

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	
};
