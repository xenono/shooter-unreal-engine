// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralShooter.h"
#include "EnemyRobotController.h"
#include "EnemyRobot.h"
#include "EnemyRobotPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"


AEnemyRobotController::AEnemyRobotController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	LocationToGoKey = "LocationToGO";
	PlayerKey = "Target";

}

