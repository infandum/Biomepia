// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectionComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE4_BIOMEPIA_API USelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USelectionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Raytrace)
		FVector StartOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Raytrace)
		FVector DirectionAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Raytrace)
		float RayDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Raytrace)
		TArray<UClass*> SelectableClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Targets)
		FHitResult HoverTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Targets)
		bool IsHovering;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Targets)
		FHitResult SelectedTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Targets)
		bool IsSelected;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Selection")
		void SelectTarget();
};
