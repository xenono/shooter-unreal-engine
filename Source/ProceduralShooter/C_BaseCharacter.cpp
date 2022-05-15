// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BaseCharacter.h"
#include "C_Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "ProceduralShooterGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	MovementComponent = this->GetCharacterMovement();
	Gun = GetWorld()->SpawnActor<AC_Gun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Muzzle_01"));
	Gun->SetOwner(this);
	CurrentMovementType = RUN;
	Health = MaxHealth;
}

// Called every frame
void AC_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		if (MovementComponent) {
			if (CurrentMovementType == RUN) {
				MovementComponent->bOrientRotationToMovement = true;
				this->bUseControllerRotationYaw = false;
			}
			else if (CurrentMovementType == AIM) {
				MovementComponent->bOrientRotationToMovement = false;
				this->bUseControllerRotationYaw = true;
			}
		}

}

// Called to bind functionality to input
void AC_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&AC_BaseCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Released,this,&AC_BaseCharacter::StopJump);

	PlayerInputComponent->BindAction(TEXT("Aim"),EInputEvent::IE_Pressed,this,&AC_BaseCharacter::StartAiming);
	PlayerInputComponent->BindAction(TEXT("Aim"),EInputEvent::IE_Released,this,&AC_BaseCharacter::StopAiming);

	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AC_BaseCharacter::Shoot);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AC_BaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AC_BaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSideways"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AC_BaseCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookSidewaysRate"), this, &AC_BaseCharacter::LookSidewaysRate);
}


void AC_BaseCharacter::MoveForward(float AxisValue)
{
	if (CurrentMovementType == RUN) {
		FRotator CharacterRotator = GetControlRotation();
		AddMovementInput(UKismetMathLibrary::GetForwardVector(CharacterRotator) * AxisValue / CurrentMovementType);
	}
	else if (CurrentMovementType == AIM) {
		AddMovementInput(GetActorForwardVector() * (AxisValue / CurrentMovementType));

	}
}

void AC_BaseCharacter::LookUpRate(float AxisValue) {
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AC_BaseCharacter::LookSidewaysRate(float AxisValue) {
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AC_BaseCharacter::MoveRight(float AxisValue)
{
	if (CurrentMovementType == RUN) {
		FRotator CharacterRotator = GetControlRotation();
		AddMovementInput(UKismetMathLibrary::GetRightVector(CharacterRotator) * (AxisValue / CurrentMovementType));
	}
	else if (CurrentMovementType == AIM) {
		AddMovementInput(GetActorRightVector() * (AxisValue / CurrentMovementType));
	}
	
}

void AC_BaseCharacter::StartJump()
{
	Jump();
}

void AC_BaseCharacter::StopJump()
{
	StopJumping();
}

void AC_BaseCharacter::StartAiming()
{
	CurrentMovementType = AIM;
	
}

void AC_BaseCharacter::StopAiming()
{
	CurrentMovementType = RUN;
}

void AC_BaseCharacter::ActivateSprint()
{
	CurrentMovementType = 1;
}

void AC_BaseCharacter::DeactivateSprint()
{
	CurrentMovementType = 2;
}

bool AC_BaseCharacter::IsAiming() const {
	return CurrentMovementType == AIM;
}

bool AC_BaseCharacter::IsDead() const
{
	if (Health <= 0) return true;
	return false;
}

float AC_BaseCharacter::GetHealthPercentage() const 
{
	return Health / MaxHealth;
}

int32 AC_BaseCharacter::GetBulletsInMagazine()
{
	return Gun->GetCurrentNumberOfBulletsInMagazine();
}

int32 AC_BaseCharacter::GetMagazineSize()
{
	return Gun->GetMagazineSize();
}

void AC_BaseCharacter::Shoot() {
	if (CurrentMovementType != AIM) return;
	Gun->PullTrigger();
}

AC_Gun* AC_BaseCharacter::GetGun()
{
	if (!Gun)return nullptr;
	return Gun;
}

float  AC_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	if (IsDead()) {
		AProceduralShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AProceduralShooterGameModeBase>();
		if (GameMode) GameMode->PawnKilled(this);
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied;
}

