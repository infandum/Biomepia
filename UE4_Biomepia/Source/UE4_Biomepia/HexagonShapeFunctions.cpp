// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonShapeFunctions.h"
#include "HexagonMath.h"

FHexagonShape::FHexagonShape() 
: Center (FVector{0,0,0})
, Corners(TArray<FVector>())
, Radius(100.f)
, Height(0.0f)
, IsPointyHexagon(true)
{
	InitializeCorners(FVector{ 0,0,0 }, 100.0f, 0.0f, true);
}

FHexagonShape::FHexagonShape(FVector position, float radius, float height, bool isPointyHex) 
: Center(position.X, position.Y, height)
, Corners(TArray<FVector>())
, Radius(radius)
, Height(height)
, IsPointyHexagon(isPointyHex)
{
	InitializeCorners({ position.X, position.Y, height }, radius, height, isPointyHex);
}

FVector FHexagonShape::GetCorner(int cornerIndex)
{
	if (Corners.Num() > 0) return Corners[cornerIndex % 6];
	
	InitializeCorners(Center, Radius, Height, IsPointyHexagon);
	return Corners[cornerIndex % 6];
}

TArray<FVector> FHexagonShape::GetCorners()
{
	if(Corners.Num() > 0) return Corners;

	InitializeCorners(Center, Radius, Height, IsPointyHexagon);
	return Corners;
}

TArray<FVector> FHexagonShape::GetTrapezoidsCenters() const
{
	return UHexagonMath::GetHexagonTrapezoidsCenters(Radius, Height, Center, IsPointyHexagon);
}

TArray<FVector> FHexagonShape::GetRhombusCenters() const
{
	return UHexagonMath::GetHexagonRhombusCenters(Radius, Height, Center, IsPointyHexagon);
}

TArray<FVector> FHexagonShape::GetTrianglesCenters() const
{
	return UHexagonMath::GetHexagonRhombusCenters(Radius, Height, Center, IsPointyHexagon);
}

void FHexagonShape::InitializeCorners(FVector position, float radius, float height, bool isPointyHex)
{
	Corners = TArray<FVector>();

	FVector2D corner = UHexagonMath::GetHexagonCorner(radius, 0, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Height });

	corner = UHexagonMath::GetHexagonCorner(radius, 1, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Height });

	corner = UHexagonMath::GetHexagonCorner(radius, 2, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Height });

	corner = UHexagonMath::GetHexagonCorner(radius, 3, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Height });

	corner = UHexagonMath::GetHexagonCorner(radius, 4, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Height });

	corner = UHexagonMath::GetHexagonCorner(radius, 5, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Height });
}





FHexagonShape UHexagonShapeFunctions::GetHexagonShape(FVector position, float radius, float height, bool isPointyHex)
{
	return FHexagonShape(position, radius, height, isPointyHex);
}

FVector UHexagonShapeFunctions::GetCenter(const FHexagonShape& hexagon)
{
	return hexagon.GetCenter();
}

TArray<FVector> UHexagonShapeFunctions::GetCorners(const FHexagonShape& hexagon)
{
	TArray<FVector> Corners = TArray<FVector>();
	FVector2D corner = FVector2D();

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 0, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetHeight() });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 1, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetHeight() });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 2, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetHeight() });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 3, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetHeight() });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 4, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetHeight() });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 5, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetHeight() });

	return Corners;
}

float UHexagonShapeFunctions::GetRadius(const FHexagonShape & hexagon)
{
	return hexagon.GetRadius();
}

float UHexagonShapeFunctions::GetHeight(const FHexagonShape & hexagon)
{
	return hexagon.GetHeight();
}

bool UHexagonShapeFunctions::GetIsPointyHexagon(const FHexagonShape & hexagon)
{
	return hexagon.GetIsPointyHexagon();
}

FVector UHexagonShapeFunctions::GetCorner(const FHexagonShape & hexagon, int cornerIndex)
{
	const FVector2D corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), cornerIndex % 6, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());	
	return { corner.X, corner.Y, hexagon.GetHeight()};
}

TArray<FVector> UHexagonShapeFunctions::GetTrapezoidsCenters(const FHexagonShape& hexagon, bool isCenteriod)
{
	return UHexagonMath::GetHexagonTrapezoidsCenters(hexagon.GetRadius(), hexagon.GetHeight(),hexagon.GetCenter(), hexagon.GetIsPointyHexagon(), isCenteriod);
}

TArray<FVector> UHexagonShapeFunctions::GetRhombusCenters(const FHexagonShape& hexagon)
{
	return UHexagonMath::GetHexagonRhombusCenters(hexagon.GetRadius(), hexagon.GetHeight(), hexagon.GetCenter(), hexagon.GetIsPointyHexagon());
}

TArray<FVector> UHexagonShapeFunctions::GetTrianglesCenters(const FHexagonShape& hexagon, bool isCenteriod)
{
	return UHexagonMath::GetHexagonTrianglesCenters(hexagon.GetRadius(), hexagon.GetHeight(), hexagon.GetCenter(), hexagon.GetIsPointyHexagon(), isCenteriod);
}
