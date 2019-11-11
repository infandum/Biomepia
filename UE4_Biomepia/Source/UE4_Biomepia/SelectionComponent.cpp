// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionComponent.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Engine/Engine.h"
#include "Math/Rotator.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
USelectionComponent::USelectionComponent()
	: StartOffset(FVector(0.0f, 0.0f, 0.0f))
	  , DirectionAxis(FVector(0.0f, 0.0f, -1.0f)), RayDistance(1000.0f)
	  , SelectableClasses(TArray<UClass*>()), HoverTarget(FHitResult()), IsHovering(false), SelectedTarget(FHitResult())
	  , IsSelected(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USelectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FHitResult USelectionComponent::SelectTarget()
{
	SelectedTarget = HoverTarget;
	IsSelected = true;
	if(SelectedTarget.GetActor() != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are Selecting: %s"), *SelectedTarget.GetActor()->GetName()));

	return SelectedTarget;

}

FHitResult USelectionComponent::GetSelectTarget()
{
	return SelectedTarget;
}

FHitResult USelectionComponent::GetHoverTarget()
{
	return HoverTarget;
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
			if (SelectableClasses.Contains(OutHit.GetActor()->GetClass()))
			{
				HoverTarget = OutHit;
				IsHovering = true;
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *OutHit.GetActor()->GetName()));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *OutHit.ImpactPoint.ToString()));
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Normal Point: %s"), *OutHit.ImpactNormal.ToString()));
			}
			else
			{
				HoverTarget = FHitResult();
				IsHovering = false;
			}
				
		}
		else
		{
			HoverTarget = FHitResult();
			IsHovering = false;
		}
	}
	else
	{
		HoverTarget = FHitResult();
		IsHovering = false;
	}
}

