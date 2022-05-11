// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALSHOOTER_API AC_ShooterAIController : public AAIController
{
	GENERATED_BODY()
public:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior;
};
