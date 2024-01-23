// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGarbageInfo.generated.h"

USTRUCT(BlueprintType)
struct  GARBAGETRUCKSIM_API FGarbageInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UStaticMesh* GarbageMesh;
	UPROPERTY(EditAnywhere)
	float Mass;
	
};
