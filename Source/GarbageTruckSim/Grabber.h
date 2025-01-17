// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GARBAGETRUCKSIM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	UPROPERTY(EditAnywhere)
	float TraceLength = 200.f;

	UPROPERTY(EditAnywhere)
	FCollisionProfileName CollisionProfile;

	UPhysicsHandleComponent* MyPhysicsHandle = nullptr;

	UInputComponent* MyInputComponent = nullptr;
	
	void SetupInputComponent();
	
	
	UFUNCTION(BlueprintCallable) float Grab();
	UFUNCTION(BlueprintCallable) void GrabEnd();
	UFUNCTION(BlueprintCallable) void Throw();
	
	FVector GetEndLineTrace();
	FTransform GetPlayerPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
