// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HexagonShapeFunctions.generated.h"

USTRUCT(BlueprintType)
struct FHexagonShape
{
	GENERATED_BODY()

	//Constructor
	FHexagonShape();
	void InitializeCorners(FVector position, float radius, float height, bool isPointyHex);
	//explicit FHexagonShape(FVector position, bool isPointyHex = true);
	explicit FHexagonShape(FVector position, float radius = 100.0f, float height = 100.0f, bool isPointyHex = true);

public:
	FVector GetCenter() const
	{
		return {Center.X, Center.Y, Height };
	}

	float GetRadius() const
	{
		return Radius;
	}

	float GetHeight() const
	{
		return Height;
	}

	bool GetIsPointyHexagon() const 
	{
		return IsPointyHexagon;
	}

	FVector GetCorner(int cornerIndex = 0);

	TArray<FVector> GetCorners();

	TArray<FVector> GetTrapezoidsCenters() const;

	TArray<FVector> GetRhombusCenters() const;

	TArray<FVector> GetTrianglesCenters() const;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = translation)
		FVector Center;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = translation)
		TArray<FVector> Corners;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = translation)
		float Radius;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = shape)
		float Height;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = shape)
		bool IsPointyHexagon;
};
/**
 * 
 */
UCLASS()
class UE4_BIOMEPIA_API UHexagonShapeFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Hexagon Geometry")
		static FHexagonShape GetHexagonShape(FVector position = FVector(0, 0, 0), float radius = 0.0f, float height = 0.0f, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static FVector GetCenter(const FHexagonShape& hexagon);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static TArray<FVector> GetCorners(const FHexagonShape& hexagon);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static float GetRadius(const FHexagonShape& hexagon);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static float GetHeight(const FHexagonShape& hexagon);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static bool GetIsPointyHexagon(const FHexagonShape& hexagon);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static FVector GetCorner(const FHexagonShape& hexagon, int cornerIndex = 0);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static TArray<FVector> GetTrapezoidsCenters(const FHexagonShape& hexagon, bool isCenteriod = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static TArray<FVector> GetRhombusCenters(const FHexagonShape& hexagon);

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		static TArray<FVector> GetTrianglesCenters(const FHexagonShape& hexagon, bool isCenteriod = true);
};
