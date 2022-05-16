// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_BaseCharacter.generated.h"

constexpr auto AIM = 3;
constexpr auto RUN = 1;

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

	UFUNCTION(BlueprintPure)
		bool IsAiming() const;
	UFUNCTION(BlueprintPure)
		bool IsDead() const;
	UFUNCTION(BlueprintPure)
		float GetHealthPercentage() const;
	UFUNCTION(BlueprintPure)
		int32 GetBulletsInMagazine();
	UFUNCTION(BlueprintPure)
		int32 GetMagazineSize();
	//UFUNCTION(BlueprintCallable)
	int32 CurrentMovementType = RUN;
	void StartAiming();
	void StopAiming();
	void Shoot();
	class AC_Gun* GetGun();
	UPROPERTY(EditAnywhere)
		float Health;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void StartJump();
	void StopJump();
	
	void ActivateSprint();
	void DeactivateSprint();
	void LookUpRate(float AxisValue);
	void LookSidewaysRate(float AxisValue);
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	APawn* PlayerPawn;
	UCharacterMovementComponent* MovementComponent = nullptr;	
	
	UPROPERTY(EditAnywhere)
	int32 RotationRate = 10.f;
	
	UPROPERTY(EditAnywhere)
		float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AC_Gun> GunClass;
	UPROPERTY()
		AC_Gun* Gun;
};
