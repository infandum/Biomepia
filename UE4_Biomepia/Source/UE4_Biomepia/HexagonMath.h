// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HexagonShapeFunctions.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HexagonMath.generated.h"

UENUM(BlueprintType)
enum class EHexagonOffset : uint8
{
	HEX_EVEN	UMETA(DisplayName = "Even"),
	HEX_ODD		UMETA(DisplayName = "Odd")
};

USTRUCT(BlueprintType)
struct FHexCubeCoordinates
{
	GENERATED_BODY()

	//Constructor
	FHexCubeCoordinates() : Q(0), R(0), S(0) {}
	FHexCubeCoordinates(int q_, int r_, int s_) : Q(q_), R(r_), S(s_)
	{
		if (Q + R + S != 0) UE_LOG(LogTemp, Warning, TEXT("Hexagonal Cube Coordinate: q + r + s must be 0!!"));
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = hexagon)
		int Q;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = hexagon)
		int R;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = hexagon)
		int S;
};

USTRUCT(BlueprintType)
struct FHexAxialCoordinates
{
	GENERATED_BODY()

	//Constructor
	FHexAxialCoordinates() : Col(0), Row(0) {}
	FHexAxialCoordinates(int col_, int row_) : Col(col_), Row(row_) {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = hexagon)
		int Col;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = hexagon)
		int Row;
};

/**
 * 
 */
UCLASS()
class UE4_BIOMEPIA_API UHexagonMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Polygon Geometry
	UFUNCTION(BlueprintPure, Category = "Polygon Geometry")
		static FVector2D GetPositionOnCircle(float rad, float radius, FVector2D center = FVector2D(0, 0));

	UFUNCTION(BlueprintPure, Category = "Polygon Geometry")
		static FVector2D TriangleCenteriod(FVector2D v0, FVector2D v1, FVector2D v2);

	UFUNCTION(BlueprintPure, Category = "Polygon Geometry")
		static FVector2D TrapezoidCenteriod2D(FVector2D v0, FVector2D v1, FVector2D v2, FVector2D v3, bool isYup = true);

	UFUNCTION(BlueprintPure, Category = "Polygon Geometry")
		static FVector TrapezoidCenteriod(FVector v0, FVector v1, FVector v2, FVector v3, bool isYup = true);

	UFUNCTION(BlueprintPure, Category = "Polygon Geometry")
		static FVector2D TrapezoidCenteriodFromHeight(float height, float base1, float base2, bool isYup = true);

	UFUNCTION(BlueprintPure, Category = "Polygon Geometry")
		static FVector2D AverageCenteriod2D(const TArray<FVector2D>& centriods, const int size);

	UFUNCTION(BlueprintPure, Category = "Polygon Geometry")
		static FVector AverageCenteriod(const TArray<FVector>& centriods, const int size);

	//Hexagonal Geometry
	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static FVector2D HexagonSize(float radius, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static float HexagonRadius(FVector2D size, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static FVector2D HexagonSpacing(FVector2D size, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static FVector2D GetHexagonCorner(float radius, int sideIndex, FVector2D center = FVector2D(0, 0), bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static float GetHexagonDegree(int sideIndex, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static float GetHexagonRad(int sideIndex, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static FHexagonShape GetHexagonShape(FVector position = FVector(0, 0, 0), float radius = 0.0f, float height = 0.0f, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static TArray<FVector> GetHexagonTrapezoidsCenters(float radius, float height = 0, FVector position = FVector(0, 0, 0), bool isPointyHex = true, bool isCenteriod = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static TArray<FVector> GetHexagonRhombusCenters(float radius, float height = 0, FVector position = FVector(0, 0, 0), bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Geometry")
		static TArray<FVector> GetHexagonTrianglesCenters(float radius, float height = 0, FVector position = FVector(0, 0, 0), bool isPointyHex = true, bool isCenteriod = true);
	
	//Hexagonal Mathematics
	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static FHexCubeCoordinates HexagonAdd(FHexCubeCoordinates a, FHexCubeCoordinates b);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static FHexCubeCoordinates HexagonSubtract(FHexCubeCoordinates a, FHexCubeCoordinates b);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static FHexCubeCoordinates HexagonScale(FHexCubeCoordinates a, int scale);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static FHexCubeCoordinates HexagonRotateLeft(FHexCubeCoordinates a);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static FHexCubeCoordinates HexagonRotateRight(FHexCubeCoordinates a);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static FHexCubeCoordinates HexagonDirection(int side);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static FHexCubeCoordinates HexagonNeighbor(FHexCubeCoordinates a, int side);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static FHexCubeCoordinates HexagonDiagonalNeighbor(FHexCubeCoordinates a, int side);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static int HexagonLength(FHexCubeCoordinates a);

	UFUNCTION(BlueprintPure, Category = "Hexagon Mathematics")
		static int HexagonDistance(FHexCubeCoordinates a, FHexCubeCoordinates b);

	//Hexagonal Coordinates
	UFUNCTION(BlueprintPure, Category = "Hexagon Coordinates")
		static FHexAxialCoordinates CubeToAxial(FHexCubeCoordinates cube);

	UFUNCTION(BlueprintPure, Category = "Hexagon Coordinates")
		static FHexCubeCoordinates AxialToCube(FHexAxialCoordinates axial);

	UFUNCTION(BlueprintPure, Category = "Hexagon Coordinates")
		static FHexAxialCoordinates CubeToOffsetAxial(EHexagonOffset offset, FHexCubeCoordinates cube, bool isPointyHex = true);

	UFUNCTION(BlueprintPure, Category = "Hexagon Coordinates")
		static FHexCubeCoordinates OffsetAxialToCube(EHexagonOffset offset, FHexAxialCoordinates axial, bool isPointyHex = true);

	//Hexagon texture functions
};
