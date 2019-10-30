// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HexagonTileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_BIOMEPIA_API UHexagonTileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHexagonTileComponent();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMesh* StaticMesh {};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* MeshComponent {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Translation)
		USceneComponent* SceneComponent {};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
