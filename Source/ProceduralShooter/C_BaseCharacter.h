// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_BaseCharacter.generated.h"

UCLASS()
class PROCEDURALSHOOTER_API AC_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void ActivateSprint();
	void DeactivateSprint();
	APawn* PlayerPawn;
	// Walk - 2 || Sprint - 1
	int32 CurrentMovementType = 2;
};
