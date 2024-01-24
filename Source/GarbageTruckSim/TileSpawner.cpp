// Fill out your copyright notice in the Description page of Project Settings.


#include "TileSpawner.h"

#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"

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
	nextTilePosition = FVector(-(SpawnTilesBehind*TileWidth),0,0);
	GetOwner()->FindComponentByTag<UBoxComponent>("BackWall")->SetRelativeLocation(FVector(-(SpawnTilesBehind*TileWidth), 0, 0));
	GetOwner()->FindComponentByTag<UBoxComponent>("FrontWall")->SetRelativeLocation(FVector(((SpawnTilesSum - SpawnTilesBehind - 2)*TileWidth), 0, 0));

	if (ActorsToSpawn.Num() > 0)
	{
		for (int i = 0; i < SpawnTilesSum; ++i)
		{
			SpawnTile();
		}
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation()+FVector(TileWidth, 0,0));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Tiles Defined"));
	}
	
	
}


void UTileSpawner::SpawnTile()
{
	spawnedActors.Add(GetWorld()->SpawnActor<AActor>(ActorsToSpawn[FMath::RandRange(0, ActorsToSpawn.Num()-1)], nextTilePosition, FRotator(0,FMath::RandBool()?0:180,0)));
	SpawnGarbageOnTile();
	nextTilePosition.X += TileWidth;
	
	
}

void UTileSpawner::RemoveFirstTile()
{
	spawnedActors[0]->Destroy();
	spawnedActors.RemoveAt(0);
}

void UTileSpawner::SpawnGarbageOnTile()
{
	if (GarbageMeshes.Num() > 0)
	{
		for (int i = 0; i < FMath::RandRange(MinGarbage, MaxGarbage); ++i)
		{
			float RandMesh = FMath::RandRange(0, GarbageMeshes.Num()-1);
			AStaticMeshActor* NewMesh = GetWorld()->SpawnActor<AStaticMeshActor>(nextTilePosition + FVector(FMath::RandRange(-1700,1700),FMath::RandBool()?-450:450,100), FRotator(FMath::RandRange(0,180), 0, 0));
			NewMesh-> SetMobility(EComponentMobility::Movable);
			NewMesh->GetStaticMeshComponent()->SetStaticMesh(GarbageMeshes[RandMesh].GarbageMesh);
			NewMesh->GetStaticMeshComponent()->SetSimulatePhysics(true);
			NewMesh->GetStaticMeshComponent()->SetGenerateOverlapEvents(true); 
			NewMesh->GetStaticMeshComponent()->BodyInstance.SetMassOverride(GarbageMeshes[RandMesh].Mass, true);
			NewMesh->GetStaticMeshComponent()->BodyInstance.UpdateMassProperties();
			NewMesh->Tags.Add("Grab");
		
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No GarbageMesh Defined"));
	}
	
}


// Called every frame
void UTileSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTileSpawner::MoveSpawnTrigger()
{
	SpawnTile();
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation()+FVector(TileWidth, 0,0));
	RemoveFirstTile();
}

