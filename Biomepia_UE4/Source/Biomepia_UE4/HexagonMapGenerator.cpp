// Fill out your copyright notice in the Description page of Project Settings.
#include "HexagonMapGenerator.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHexagonMapGenerator::AHexagonMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));	
	m_Mesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AHexagonMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHexagonMapGenerator::OnConstruction(const FTransform& Transform)
{
	m_Mesh->SetStaticMesh(m_HexagonMesh);
	for (int x = 1; x <= 3; x++)
	{
		int maxHex = 360 / (60 / x);
		for (int index = 1; index <= 6; index++)
		{
			//Spawn Hexagon points
			int angle = (60 * index) + 30;
			FVector pos = FVector();
			pos = PointOnCircle(angle * (PI / 180), x);
			pos = FVector(FMath::RoundToInt(pos.X * 1000.0f) / 1000.0f, FMath::RoundToInt(pos.Y * 1000.0f) / 1000.0f, 0);
			//pos = new FVector(Mathf.Round(pos.x * 1000.0f) , 0, Mathf.Round(pos.z * 1000.0f) / 1000.0f);
		}
	}
}

void AHexagonMapGenerator::CreateHexagonalHexMap()
{

}

FVector AHexagonMapGenerator::HexCorners(const FVector center, const float size, const int sideIndex, const bool isPointyHex)
{
	const float angle_deg = 60 * sideIndex + ((isPointyHex == false) ? 0 : 30);
	const float angle_rad = PI / 180 * angle_deg;
	return FVector(center.X + size * FMath::Cos(angle_rad), center.Y + size * FMath::Sin(angle_rad), 0);
}

FVector AHexagonMapGenerator::PointOnCircle(float rad, float radius)
{
	FVector position;
	float x = radius * FMath::Sin(rad);
	float y = radius * FMath::Cos(rad);
	float z = 0;
	return FVector(x,y,z);
}

// Called every frame
void AHexagonMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

