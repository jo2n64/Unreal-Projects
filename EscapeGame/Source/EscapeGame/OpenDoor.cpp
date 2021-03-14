// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	OnOpen.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	OnClose.Broadcast();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOfActorsOnPlate() > 10.0f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else {
		CloseDoor();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate() const {
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const AActor* Actor : OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *Actor->GetName());
		float ActorMass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += ActorMass;
	}
	
	return TotalMass;
}

