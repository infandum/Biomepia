// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexagonMapGenerator.generated.h"

UCLASS()
class BIOMEPIA_UE4_API AHexagonMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexagonMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	void CreateHexagonalHexMap();
private:
	static FVector HexCorners(FVector center, float size, int sideIndex, bool isPointyHex = true);
	static FVector PointOnCircle(float rad, float radius);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMesh* m_HexagonMesh;

	UPROPERTY(/*EditAnywhere*/)
	UStaticMeshComponent* m_Mesh;

};
