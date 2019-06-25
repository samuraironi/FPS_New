// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	_navMeshBoundVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bound Volume Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolume()
{
	auto volumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (volumeIterator)
	{
		AddToPool(*volumeIterator);
		++volumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *volumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Found actor: %s"), *volumeToAdd->GetName());
}
