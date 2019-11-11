// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"
#include "HexagonMath.h"
#include "HexagonShapeFunctions.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h" 	
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
AHexagonTile::AHexagonTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HexagonTileInit();
}

AHexagonTile::AHexagonTile(FHexCubeCoordinates coord, FVector2D uv, FHexagonShape HexagonShape)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//SetTileData(coord, elevation, uv, HexagonShape);

	HexagonTileInit();
}

void AHexagonTile::HexagonTileInit()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComponent->Mobility = EComponentMobility::Movable;
	RootComponent = SceneComponent;

	if (StaticMesh == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("No default mesh was set, setting default 1M_Hexagon"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObj(TEXT("/Game/Geometry/Meshes/1M_Hexagon"));
		StaticMesh = StaticMeshObj.Object;
	}

	if (StaticMesh)
	{
		//UE_LOG(LogTemp, Log, TEXT("Setting StaticMeshComponent"));
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		MeshComponent->SetStaticMesh(StaticMesh);

		MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));


	}
	//else
	//	UE_LOG(LogTemp, Warning, TEXT("No Static Mesh!!"));
}


// Called when the game starts or when spawned
void AHexagonTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexagonTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexagonTile::OnConstruction(const FTransform & Transform)
{
}


//void AHexagonTile::SetTileData(FHexCubeCoordinates coord, FVector2D uv, FHexagonShape hexagonShape)
//{
//	const FString name = "Hex:" + FString::FromInt(coord.Q) + "," + FString::FromInt(coord.R) + "," + FString::FromInt(coord.S);
//	//GetOwner()->Rename(*name);
//	//GetOwner()->SetActorLabel(*name);
//	//Rename(*name);
//	//SetActorLabel(*name);
//	Coordinates = coord;
//	HeightUV = uv;
//	HexagonShape = hexagonShape;
//}


void AHexagonTile::SetHeight(const float height) const
{
	FVector currentPos = RootComponent->GetRelativeTransform().GetLocation();
	currentPos.Z = height;
	RootComponent->SetRelativeLocation(currentPos);
}

void AHexagonTile::SetElevation(float value)
{
	HeightElevation = value;
}

void AHexagonTile::SetTileData(FHexCubeCoordinates coord, FVector2D uv, FHexagonShape hexShape)
{
	Coordinates = coord;
	HeightUV = uv;
	HexagonShape = hexShape;
}

void AHexagonTile::SetDynamicMaterial(FLinearColor linearColor, UMaterialInterface* baseMaterial)
{
	if(baseMaterial == nullptr)
		DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(0), this);
	else
	{
		if (DynamicMaterial == nullptr)
			DynamicMaterial = UMaterialInstanceDynamic::Create(baseMaterial, this);
	}

	DynamicMaterial->SetVectorParameterValue("Color", linearColor);
	MeshComponent->SetMaterial(0, DynamicMaterial);
}