// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AInfiniteTerrainGameMode : public AFPSGameMode
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolume();
	
private:
	void AddToPool(class ANavMeshBoundsVolume* volumeToAdd);
};
