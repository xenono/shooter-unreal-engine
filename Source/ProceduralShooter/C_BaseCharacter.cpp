// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AC_BaseCharacter::AC_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void AC_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerPawn) {
		FVector Location = PlayerPawn->GetActorLocation();
		UE_LOG(LogTemp, Error, TEXT("%f"), Location.X);
	}
	
}

// Called to bind functionality to input
void AC_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AC_BaseCharacter::ActivateSprint()
{
	CurrentMovementType = 1;
}

void AC_BaseCharacter::DeactivateSprint()
{
	CurrentMovementType = 2;
}

