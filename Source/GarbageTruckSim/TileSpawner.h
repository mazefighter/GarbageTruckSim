// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGarbageInfo.h"
#include "Components/ActorComponent.h"
#include "TileSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GARBAGETRUCKSIM_API UTileSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTileSpawner();

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> spawnedActors;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> ActorsToSpawn;

	UPROPERTY(EditAnywhere, Category= "Garbage")
	TArray<FGarbageInfo> GarbageMeshes;

	UPROPERTY(EditAnywhere, Category= "Garbage")
	float MinGarbage = 5;
	UPROPERTY(EditAnywhere, Category= "Garbage")
	float MaxGarbage = 20;
	
	

	UPROPERTY(EditAnywhere, Category= "TilePositions")
	float TileWidth = 3600;

	UPROPERTY(EditAnywhere, Category= "TilePositions")
	int SpawnTilesSum = 10;

	UPROPERTY(EditAnywhere, Category= "TilePositions")
	int SpawnTilesBehind = 4;
	
	FVector nextTilePosition;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SpawnTile();
	void RemoveFirstTile();
	void SpawnGarbageOnTile();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) void MoveSpawnTrigger();

		
};
