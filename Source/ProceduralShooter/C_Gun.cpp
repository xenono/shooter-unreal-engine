// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Gun.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AC_Gun::AC_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AC_Gun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_Gun::PullTrigger() {
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(2,2,2), FColor::Red, true);
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("Muzzle_01"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("Muzzle_01"));
}

