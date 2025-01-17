// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	

	MyPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!MyPhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Kein UPhysicsHandleComponent"))
	}

	SetupInputComponent();
	
}

void UGrabber::SetupInputComponent()
{
	MyInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (MyInputComponent)
	{
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Kein UInputComponent"))
	}
}

float UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab!"))
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld() -> LineTraceSingleByObjectType(Hit, GetPlayerPoint().GetLocation(), GetEndLineTrace(), FCollisionObjectQueryParams(), TraceParams);
	if (Hit.GetActor() && (Hit.GetComponent()->ComponentTags.Contains("Grab") || Hit.GetActor()->Tags.Contains("Grab")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Grab Hit!"))
		MyPhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, GetEndLineTrace());
		Hit.GetComponent()->SetSimulatePhysics(true);
		Hit.GetComponent()->SetGenerateOverlapEvents(true);
		Hit.GetComponent()->SetCollisionProfileName(CollisionProfile.Name, true);
		return MyPhysicsHandle->GrabbedComponent->BodyInstance.GetBodyMass();
	}
		return 0;
}



void UGrabber::GrabEnd()
{
	if (MyPhysicsHandle->GrabbedComponent)
	{
		MyPhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Throw()
{
	if (MyPhysicsHandle->GrabbedComponent)
	{
		UPrimitiveComponent* throwObject = MyPhysicsHandle->GrabbedComponent;
		GrabEnd();
		throwObject->AddForce(FVector(GetPlayerPoint().Rotator().Vector() * (1000000 - throwObject->BodyInstance.GetBodyMass() * 1000)));
	}
}

FVector UGrabber::GetEndLineTrace()
{
	return GetPlayerPoint().GetLocation() + GetPlayerPoint().GetRotation().Vector() * TraceLength;
}

FTransform UGrabber::GetPlayerPoint()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	

	GetWorld()->GetFirstPlayerController() -> GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	return FTransform(PlayerViewPointRotation, PlayerViewPointLocation);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugLine(GetWorld(), GetPlayerPoint().GetLocation(), GetEndLineTrace(), FColor(0,255,0));

	if (MyPhysicsHandle->GrabbedComponent)
	{
		MyPhysicsHandle->SetTargetLocation(GetEndLineTrace());
	}
}

