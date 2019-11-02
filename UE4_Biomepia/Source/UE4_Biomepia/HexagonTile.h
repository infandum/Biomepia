// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexagonTile.generated.h"

UCLASS()
class UE4_BIOMEPIA_API AHexagonTile : public AActor
{
	GENERATED_BODY()
	
public:
	void HexagonTileInit();
	// Sets default values for this actor's properties
	AHexagonTile();
	AHexagonTile(FVector index, FVector2D uv);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMesh* StaticMesh{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* MeshComponent {};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	UMaterialInstanceDynamic* DynamicMaterial{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Translation)
	USceneComponent* SceneComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data)
	FVector LocationIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data)
	FVector2D HeightUV;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Data)
	// HeightUV;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnConstruction(const FTransform & Transform) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
	void SetHeight(const float height) const;

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
	float GetHeight() const { return RootComponent->GetRelativeTransform().GetLocation().Z; }

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
	void SetElevation(float elevation);

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
	float GetElevation() const { return LocationIndex.Z; }

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
	FVector2D GetHeightUV() const { return HeightUV; }

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
	void SetTileData(FVector index, FVector2D uv);

	UFUNCTION(BlueprintCallable, Category = "HexagonTile")
	void SetDynamicMaterial(FLinearColor linearColor, UMaterialInterface* baseMaterial = nullptr);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
