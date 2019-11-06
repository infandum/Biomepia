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
: Center(position)
, Corners(TArray<FVector>())
, Radius(radius)
, Height(height)
, IsPointyHexagon(isPointyHex)
{
	InitializeCorners(position, radius, height, isPointyHex);
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

//TArray<FVector> FHexagonShape::GetCorners() 
//{
//
//	Corners = TArray<FVector>();
//
//	FVector2D corner = UHexagonMath::GetHexagonCorner(Radius, 0, { Center.X, Center.Y }, IsPointyHexagon);
//	Corners.Add({ corner.X, corner.Y, Center.Z });
//
//	corner = UHexagonMath::GetHexagonCorner(Radius, 0, { Center.X, Center.Y }, IsPointyHexagon);
//	Corners.Add({ corner.X, corner.Y, Center.Z });
//
//	corner = UHexagonMath::GetHexagonCorner(Radius, 1, { Center.X, Center.Y }, IsPointyHexagon);
//	Corners.Add({ corner.X, corner.Y, Center.Z });
//
//	corner = UHexagonMath::GetHexagonCorner(Radius, 2, { Center.X, Center.Y }, IsPointyHexagon);
//	Corners.Add({ corner.X, corner.Y, Center.Z });
//
//	corner = UHexagonMath::GetHexagonCorner(Radius, 3, { Center.X, Center.Y }, IsPointyHexagon);
//	Corners.Add({ corner.X, corner.Y, Center.Z });
//
//	corner = UHexagonMath::GetHexagonCorner(Radius, 4, { Center.X, Center.Y }, IsPointyHexagon);
//	Corners.Add({ corner.X, corner.Y, Center.Z });
//
//	corner = UHexagonMath::GetHexagonCorner(Radius, 5, { Center.X, Center.Y }, IsPointyHexagon);
//	Corners.Add({ corner.X, corner.Y, Center.Z });
//
//	return Corners;
//}

void FHexagonShape::InitializeCorners(FVector position, float radius, float height, bool isPointyHex)
{
	Corners = TArray<FVector>();

	FVector2D corner = UHexagonMath::GetHexagonCorner(radius, 0, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Center.Z });

	corner = UHexagonMath::GetHexagonCorner(radius, 0, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Center.Z });

	corner = UHexagonMath::GetHexagonCorner(radius, 1, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Center.Z });

	corner = UHexagonMath::GetHexagonCorner(radius, 2, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Center.Z });

	corner = UHexagonMath::GetHexagonCorner(radius, 3, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Center.Z });

	corner = UHexagonMath::GetHexagonCorner(radius, 4, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Center.Z });

	corner = UHexagonMath::GetHexagonCorner(radius, 5, { Center.X, Center.Y }, isPointyHex);
	Corners.Add({ corner.X, corner.Y, Center.Z });
}


//FVector UHexagonShapeFunctions::GetCenters(UPARAM(ref) FHexagonShape& hexagon)
//{
//	return hexagon.GetCenter();
//}

FVector UHexagonShapeFunctions::GetCenter(const FHexagonShape& hexagon)
{
	return hexagon.GetCenter();
}

TArray<FVector> UHexagonShapeFunctions::GetCorners(const FHexagonShape& hexagon)
{
	TArray<FVector> Corners = TArray<FVector>();
	FVector2D corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 0, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetCenter().Z });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 0, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetCenter().Z });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 1, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetCenter().Z });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 2, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetCenter().Z });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 3, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetCenter().Z });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 4, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetCenter().Z });

	corner = UHexagonMath::GetHexagonCorner(hexagon.GetRadius(), 5, { hexagon.GetCenter().X, hexagon.GetCenter().Y }, hexagon.GetIsPointyHexagon());
	Corners.Add({ corner.X, corner.Y, hexagon.GetCenter().Z });

	return Corners;
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

TArray<FVector> UHexagonShapeFunctions::GetRhombusCenters(const FHexagonShape& hexagon, bool isCenteriod)
{
	return UHexagonMath::GetHexagonRhombusCenters(hexagon.GetRadius(), hexagon.GetHeight(), hexagon.GetCenter(), hexagon.GetIsPointyHexagon(), isCenteriod);
}

TArray<FVector> UHexagonShapeFunctions::GetTrianglesCenters(const FHexagonShape& hexagon, bool isCenteriod)
{
	return UHexagonMath::GetHexagonTrianglesCenters(hexagon.GetRadius(), hexagon.GetHeight(), hexagon.GetCenter(), hexagon.GetIsPointyHexagon(), isCenteriod);
}
