// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "C_BaseCharacter.h"

// Sets default value
AHealthPickUp::AHealthPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MySphereComponent->InitSphereRadius(200.f);
	MySphereComponent->SetCollisionProfileName(TEXT("Trigger"));	

	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickUp::OnOverlapBegin);
	 
}

void AHealthPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	AC_BaseCharacter* Player = Cast<AC_BaseCharacter>(OtherActor);
	Player->Health += 30.f;
	Destroy();	
	
}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

AController* AHealthPickUp::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;
	return OwnerPawn->GetController();
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

