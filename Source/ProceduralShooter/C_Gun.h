// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Gun.generated.h"

UCLASS()
class PROCEDURALSHOOTER_API AC_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Gun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PullTrigger();
	float GetGunDamage();
	
private:
	bool BulletTrace(FHitResult& Hit, FVector& ShotDirection);
	AController* GetOwnerController() const;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
		class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
		UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere)
		USoundBase* HitSound;
	UPROPERTY(EditAnywhere)
		float MaxRange = 5000.f;
	UPROPERTY(EditAnywhere)
		float GunDamage = 10.f;
};
