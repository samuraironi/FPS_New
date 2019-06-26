// Fill out your copyright notice in the Description page of Project Settings.
#include "Tile.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
}

void ATile::SetPool(UActorPool * pool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(pool->GetName()));
	_pool = pool;

	PositionNavMeshBoundVolume();
}

void ATile::PositionNavMeshBoundVolume()
{
	NavMeshBoundVolume = _pool->Checkout();
	if (NavMeshBoundVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enough actors in pool"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: [%s]"), *GetName(), *NavMeshBoundVolume->GetName());
	NavMeshBoundVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	auto navSystem = GetWorld()->GetNavigationSystem();
	navSystem->Build();
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ATile::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	_pool->Return(NavMeshBoundVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> toSpawn, int minSpawn, int maxSpawn, float radius, float minScale, float maxScale)
{
	TArray<FSpawnPosition> spawnPositions = RandomSpawnPositions(minSpawn, maxSpawn, radius, minScale, maxScale)
	for (FSpawnPosition spawnPosition : spawnPositions)
	{
		PlaceActor(toSpawn, spawnPosition);
	}
}

TArray<FSpawnPosition> ATile::RandomSpawnPositions(int minSpawn, int maxSpawn, float radius, float minScale, float maxScale)
{
	TArray<FSpawnPosition> spawnPositions;
	int numberToSpawn = FMath::RandRange(minSpawn, maxSpawn);
	for (size_t i = 0; i < numberToSpawn; i++)
	{
		FSpawnPosition spawnPosition;
		spawnPosition.Scale = FMath::RandRange(minScale, maxScale);
		bool found = FindEmptylocation(radius * spawnPosition.Scale, spawnPosition.Location);
		if (found)
		{
			spawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			spawnPositions.Add(spawnPosition);
		}
	}
	return spawnPositions;
}

bool ATile::FindEmptylocation(float radius, FVector& outLocation)
{
	FBox bounds(MinExtent, MaxExtent);
	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector candidatePoint = FMath::RandPointInBox(bounds);
		if (CanSpawnAtLocation(candidatePoint, radius))
		{
			outLocation = candidatePoint;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> toSpawn, const FSpawnPosition& spawnPosition)
{
	AActor* spawned = GetWorld()->SpawnActor<AActor>(toSpawn);
	spawned->SetActorRelativeLocation(spawnPosition.Location);
	spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	spawned->SetActorRotation(FRotator(0, spawnPosition.Rotation, 0));
	spawned->SetActorScale3D(FVector(spawnPosition.Scale));
}

bool ATile::CanSpawnAtLocation(FVector location, float radius)
{
	FHitResult hitResult;
	FVector globalLocation = ActorToWorld().TransformPosition(location);
	bool hasHit = GetWorld()->SweepSingleByChannel(
		hitResult,
		globalLocation,
		globalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(radius)
	);
	//FColor resultColor = hasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), location, 0, radius, FQuat::Identity ,resultColor, true, 100);
	return !hasHit;
}

