// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Gun.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

// Sets default values
AC_Gun::AC_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AC_Gun::BeginPlay()
{
	Super::BeginPlay();
	BindToInput();
	if (!ErrorSound || !MuzzleFlash || !MuzzleSound || !HitEffect) {
		UE_LOG(LogTemp, Error, TEXT("Sound or particle system not found!"));
	}
	BulletsInMagazine = MagazineSize;

}

// Called every frame
void AC_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_Gun::BindToInput()
{
	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent) {
		InputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AC_Gun::Reload);
		EnableInput(GetWorld()->GetFirstPlayerController());
	}

}

void AC_Gun::PullTrigger() {
	
	if (BulletsInMagazine <= 0) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ErrorSound, GetActorLocation());
		return;
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),MuzzleFlash,GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), MuzzleSound, GetActorLocation());
	FHitResult Hit;
	FVector ShotDirection;
	bool hitSuccess = BulletTrace(Hit, ShotDirection);
	if (hitSuccess) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.Location);

		AActor* HitActor = Hit.GetActor();
		AController* OwnerController = GetOwnerController();
		if (!HitActor || !OwnerController) return;
		FPointDamageEvent DamageEvent(GunDamage, Hit, ShotDirection, nullptr);
		HitActor->TakeDamage(GunDamage, DamageEvent, OwnerController, this);
	}
	BulletsInMagazine--;
}

bool AC_Gun::BulletTrace(FHitResult &Hit, FVector& ShotDirection) {
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return false;
	FVector Location(0);
	FRotator Rotation(0);
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AC_Gun::GetOwnerController() const 
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;
	return OwnerPawn->GetController();
}

void AC_Gun::Reload()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), CoolingDownSound, GetActorLocation());
	BulletsInMagazine = MagazineSize;
}

float AC_Gun::GetGunDamage() {
	return GunDamage;
}

int32 AC_Gun::GetCurrentNumberOfBulletsInMagazine() {
	return BulletsInMagazine;
}


int32 AC_Gun::GetMagazineSize() {
	return MagazineSize;
}
