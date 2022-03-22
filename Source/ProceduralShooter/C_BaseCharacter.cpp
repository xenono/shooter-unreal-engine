// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
}

// Called every frame
void AC_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AC_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&AC_BaseCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Released,this,&AC_BaseCharacter::StopJump);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AC_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AC_BaseCharacter::MoveRight);
}

void AC_BaseCharacter::MoveForward(float AxisValue)
{
	FRotator CharacterRotator = GetControlRotation();
	AddMovementInput(UKismetMathLibrary::GetForwardVector(CharacterRotator) * AxisValue);
}

void AC_BaseCharacter::MoveRight(float AxisValue)
{
	FRotator CharacterRotator = GetControlRotation();
	AddMovementInput(UKismetMathLibrary::GetRightVector(CharacterRotator) * AxisValue);
}

void AC_BaseCharacter::StartJump()
{
	Jump();
}

void AC_BaseCharacter::StopJump()
{
	StopJumping();
}

void AC_BaseCharacter::ActivateSprint()
{
	CurrentMovementType = 1;
}

void AC_BaseCharacter::DeactivateSprint()
{
	CurrentMovementType = 2;
}

