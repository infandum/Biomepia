// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HexagonMath.h"
#include "HexagonShapeFunctions.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexagonTile.generated.h"

struct FHexCubeCoordinates;
struct FHexagonShape;

UCLASS()
class UE4_BIOMEPIA_API AHexagonTile : public AActor
{
	GENERATED_BODY()
	
public:

	
	// Sets default values for this actor's properties
	AHexagonTile();
	explicit AHexagonTile(FHexCubeCoordinates coord, FVector2D uv, FHexagonShape hexagonShape);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMesh* StaticMesh{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* MeshComponent {};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
		UMaterialInstanceDynamic* DynamicMaterial{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Translation)
		USceneComponent* SceneComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data)
		FHexagonShape HexagonShape;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data)
		FHexCubeCoordinates Coordinates {};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data)
		float HeightElevation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data)
		FVector2D HeightUV;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnConstruction(const FTransform & Transform) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
		void SetHeight(const float height) const;

	UFUNCTION(BlueprintPure, Category = "HexagonTile")
		float GetHeight() const { return RootComponent->GetRelativeTransform().GetLocation().Z; }

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
		void SetElevation(float value);

	UFUNCTION(BlueprintPure, Category = "HexagonTile")
		float GetElevation() const { return HeightElevation; }

	UFUNCTION(BlueprintPure, Category = "HexagonTile")
		FHexagonShape GetHexagonalShape() const { return HexagonShape; }

	UFUNCTION(BlueprintPure, Category = "HexagonTile")
		FHexCubeCoordinates GetCoordinates() const { return Coordinates; }

	UFUNCTION(BlueprintPure, Category = "HexagonTile")
		FVector2D GetHeightUV() const { return HeightUV; }

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
		void SetTileData(FHexCubeCoordinates coord, FVector2D uv, FHexagonShape hexShape);

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
		void SetDynamicMaterial(FLinearColor linearColor, UMaterialInterface* baseMaterial = nullptr);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void HexagonTileInit();
};
