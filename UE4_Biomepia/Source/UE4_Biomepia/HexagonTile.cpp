// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTile.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHexagonTile::AHexagonTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	//SceneComponent->Mobility = EComponentMobility::Static;
	RootComponent = SceneComponent;

	if(StaticMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No default mesh was set, setting default 1M_Hexagon"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObj(TEXT("/Game/Geometry/Meshes/1M_Hexagon"));
		StaticMesh = StaticMeshObj.Object;
	}

	if (StaticMesh)
	{
		UE_LOG(LogTemp, Log, TEXT("Setting StaticMeshComponent"));
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		MeshComponent->SetStaticMesh(StaticMesh);

		MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("No Static Mesh!!"));
}

AHexagonTile::AHexagonTile(FVector index, FVector2D uv)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetTileData(index, uv);

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	//SceneComponent->Mobility = EComponentMobility::Static;
	RootComponent = SceneComponent;

	if (StaticMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No default mesh was set, setting default 1M_Hexagon"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObj(TEXT("/Game/Geometry/Meshes/1M_Hexagon"));
		StaticMesh = StaticMeshObj.Object;
	}

	if (StaticMesh)
	{
		UE_LOG(LogTemp, Log, TEXT("Setting StaticMeshComponent"));
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		MeshComponent->SetStaticMesh(StaticMesh);

		MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("No Static Mesh!!"));
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

void AHexagonTile::SetElevation(float elevation)
{
	FVector currentPos = RootComponent->GetRelativeTransform().GetLocation();
	currentPos.Z = elevation;
	RootComponent->SetRelativeLocation(currentPos);

	SetTileData(FVector(LocationIndex.X, LocationIndex.Y, elevation), HeightUV);
}

void AHexagonTile::SetTileData(FVector index, FVector2D uv)
{
	const FString name = "Hex:" + FString::SanitizeFloat(index.X) + "," + FString::SanitizeFloat(index.Y);
	//SetActorLabel(name);
	Rename(ToCStr(name));
	LocationIndex = index;
	HeightUV = uv;
}

void AHexagonTile::OnConstruction(const FTransform & Transform)
{
}
