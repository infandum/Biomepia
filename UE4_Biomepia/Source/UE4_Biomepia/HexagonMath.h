// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HexagonShapeFunctions.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HexagonMath.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BIOMEPIA_API UHexagonMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Hexagon Math")
		static FVector2D GetPositionOnCircle(float rad, float radius, FVector2D center = FVector2D(0, 0));

	UFUNCTION(BlueprintPure, Category = "Hexagon Math")
		static FVector2D GetHexagonCorner(float radius, int sideIndex, FVector2D center = FVector2D(0, 0), bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Math")
		static float GetHexagonDegree(int sideIndex, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Math")
		static float GetHexagonRad(int sideIndex, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Math")
		static FHexagonShape GetHexagonShape(FVector position = FVector(0, 0, 0), float radius = 0.0f, float height = 0.0f, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Math")
		static TArray<FVector> GetHexagonTrapezoidsCenters(float radius, float height = 0, FVector position = FVector(0, 0, 0), bool isPointyHex = true, bool isCenteriod = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Math")
		static TArray<FVector> GetHexagonRhombusCenters(float radius, float height = 0, FVector position = FVector(0, 0, 0), bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Math")
		static TArray<FVector> GetHexagonTrianglesCenters(float radius, float height = 0, FVector position = FVector(0, 0, 0), bool isPointyHex = true);
};
