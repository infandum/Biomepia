// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_BIOMEPIA_API USelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USelectionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Raytrace)
		FVector StartOffset = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Raytrace)
		FVector DirectionAxis = FVector(0.0f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Raytrace)
		float RayDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Raytrace)
		TArray<UClass*> SelectableClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Targets)
		FHitResult HoverTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Targets)
		FHitResult SelectedTarget;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
