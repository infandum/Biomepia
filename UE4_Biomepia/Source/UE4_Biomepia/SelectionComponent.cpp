// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionComponent.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Engine/Engine.h"
#include "Math/Rotator.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
USelectionComponent::USelectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USelectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult OutHit;
	const FVector Start = GetOwner()->GetActorLocation() + StartOffset;

	FVector End = GetOwner()->GetActorRotation().RotateVector(DirectionAxis * 10);
	End = (End.GetSafeNormal() * RayDistance) + Start;

	const FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams))
	{
		if (OutHit.bBlockingHit)
		{
			if (SelectableClasses.Contains(OutHit.GetActor()->GetClass())) {
				
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));

			}
		}
	}
}

