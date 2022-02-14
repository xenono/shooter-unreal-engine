// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UC_Character::UC_Character()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
  GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCharacterMovement()->bIgnoreBaseRotation = true;

	// ...
}


// Called when the game starts
void UC_Character::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using Character.cpp"));
	
}


// Called every frame
void UC_Character::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UC_Character::MoveForward(float AxisValue)
{
  if (AxisValue != 0.0f)
  {
    // Find out which way is forward

    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // Get forward vector
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(Direction, AxisValue);
  }
}

void UC_Character::MoveRight(float AxisValue)
{
  if (AxisValue != 0.0f)
  {
    // Find out which way is right
    
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    // Get right vector 
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // Add movement in that direction
    AddMovementInput(Direction, AxisValue);
  }
}

