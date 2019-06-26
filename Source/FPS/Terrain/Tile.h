// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};


class UActorPool;

UCLASS()
class FPS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceActors(TSubclassOf<AActor> toSpawn, int minSpawn = 1, int maxSpawn = 1, float radius = 500, float minScale =1, float maxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAIPawns(TSubclassOf<APawn> toSpawn, int minSpawn = 1, int maxSpawn = 1, float radius = 500);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;


	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;


	UPROPERTY(EditDefaultsOnly,  Category = "Nawigation")
	FVector NavigationBoundsOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* pool);

	
private:
	bool FindEmptylocation(float radius, FVector& outLocation);
	void PlaceActor(TSubclassOf<AActor> toSpawn, const FSpawnPosition& spawnPosition);
	void PlaceAIPawn(TSubclassOf<APawn> toSpawn, FSpawnPosition spawnPosition);
	bool CanSpawnAtLocation(FVector location, float radius);
	void PositionNavMeshBoundVolume();
	TArray<FSpawnPosition> RandomSpawnPositions(int minSpawn, int maxSpawn, float radius, float minScale, float maxScale);

	UActorPool* _pool;
	AActor* NavMeshBoundVolume;
};
