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
	explicit FHexagonShape(FVector position, bool isPointyHex = true);
	explicit FHexagonShape(FVector position, float radius = 100.0f, float height = 100.0f, bool isPointyHex = true);

	FVector GetCenter() const
	{
		return Center;
	}

	TArray<FVector> GetCorners()const
	{
		return Corners;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector Center;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FVector> Corners;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Radius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FHexagonShape HexagonShape;

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		FVector GetCenters(UPARAM(ref) FHexagonShape& shape) const;

	UFUNCTION(BlueprintPure, Category = "Hexagon Shape")
		TArray<FVector> GetCorners(UPARAM(ref) FHexagonShape& shape) const;
};
