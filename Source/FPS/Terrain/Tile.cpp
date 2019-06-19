// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors()
{
	FVector min(0, -200, 0);
	FVector max(4000, 2000, 0);
	FBox bounds(min, max);
	for (size_t i = 0; i < 20; i++)
	{
		FVector spawnPoint = FMath::RandPointInBox(bounds);
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

