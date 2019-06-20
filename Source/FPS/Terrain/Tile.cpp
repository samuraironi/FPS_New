// Fill out your copyright notice in the Description page of Project Settings.
#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> toSpawn, int minSpawn, int maxSpawn)
{
	FVector min(0, -2000, 0);
	FVector max(4000, 2000, 0);
	FBox bounds(min, max);
	int numberToSpawn = FMath::RandRange(minSpawn, maxSpawn);
	for (size_t i = 0; i < numberToSpawn; i++)
	{
		FVector spawnPoint = FMath::RandPointInBox(bounds);
		AActor* spawned = GetWorld()->SpawnActor<AActor>(toSpawn);
		spawned->SetActorRelativeLocation(spawnPoint);
		spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	CastSphere(GetActorLocation(), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CastSphere(FVector location, float radius)
{
	FHitResult hitResult;
	bool hasHit = GetWorld()->SweepSingleByChannel(
		hitResult,
		location,
		location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(radius)
	);
	FColor resultColor = hasHit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), location, 0, radius,FQuat::Identity ,resultColor, true, 100);
	return hasHit;
}

