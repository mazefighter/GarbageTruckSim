// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSpawner.h"

// Sets default values for this component's properties
UTileSpawner::UTileSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTileSpawner::BeginPlay()
{
	Super::BeginPlay();
	nextTilePosition = FVector(0,0,0);

	if (ActorsToSpawn.Num() > 0)
	{
		for (int i = 0; i < 10; ++i)
		{
			SpawnTile();
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Tiles Defined"));
	}
	
	
}

void UTileSpawner::SpawnTile()
{
	spawnedActors.Add(GetWorld()->SpawnActor<AActor>(ActorsToSpawn[FMath::RandRange(0, ActorsToSpawn.Num()-1)], nextTilePosition, FRotator(0,FMath::RandBool()?0:180,0)));
	nextTilePosition.X += 3600;
}


// Called every frame
void UTileSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

