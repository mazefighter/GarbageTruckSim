// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
	FVector nextTilePosition;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SpawnTile();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
