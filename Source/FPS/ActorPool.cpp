// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor * UActorPool::Checkout()
{
	return nullptr;
}

void UActorPool::Return(AActor * actorToReturn)
{
	if (actorToReturn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("returned no actor"));
		return;
	}
}

void UActorPool::Add(AActor * actorToAdd)
{
	if (actorToAdd == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("added no actor"));
		return;
	}
	Return(actorToAdd);
}
