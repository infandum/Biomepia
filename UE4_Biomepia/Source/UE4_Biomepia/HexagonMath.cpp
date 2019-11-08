// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonMath.h"
#include "Engine/Engine.h"

//TODO: Move too polygon math
FVector2D UHexagonMath::GetPositionOnCircle(float rad, float radius, FVector2D center)
{
	const float x = radius * FMath::Sin(rad);
	const float y = radius * FMath::Cos(rad);

	return { center.X + x, center.Y + y};
}
//TODO: Move too polygon math
FVector2D UHexagonMath::TriangleCenteriod(FVector2D v0, FVector2D v1, FVector2D v2)
{
	float x = (v0.X + v1.X + v2.X) / 3;
	float y = (v0.Y + v1.Y + v2.Y) / 3;
	return FVector2D(x, y);
}
//TODO: FIX Trapaziod function
//upright orrientated trapeziod, CLOCK-WISE winding!
//   ___
//  /   \
// '-----'
FVector UHexagonMath::TrapezoidCenteriod(FVector v0, FVector v1, FVector v2, FVector v3, bool isYup)
{
	const float h = isYup == true ? FVector::Distance((v0 + v1) / 2, (v2 + v3) / 2) : FVector::Distance((v1 + v2) / 2, (v0 + v3) / 2);
	const float w = (v2.X + v3.X) / 2;
	const float z = ((v0.Z + v1.Z + v2.Z + v3.Z) / 4);

	const float b1 = isYup == true ? FVector::Distance(v1, v2) : FVector::Distance(v0, v1);
	const float b2 = isYup == true ? FVector::Distance(v0, v3) : FVector::Distance(v2, v3);
	
	float offset = ((b1 + (2 * b1)) / (3 * (b1 + b2))) * h;
	//TODO: check this if?
	return FVector(offset, w / 2, z);
}

FVector2D UHexagonMath::TrapezoidCenteriodFromHeight(float height, float base1, float base2, bool isYup)
{
	float centeriod = ((base1 + (2 * base1)) / (3 * (base1 + base2))) * height;
	return FVector2D( (base1 + base2) / 4, centeriod);
}

//upright orrientated trapeziod, CLOCK-WISE winding!
//   ___
//  /   \
// '-----'
FVector2D UHexagonMath::TrapezoidCenteriod2D(FVector2D v0, FVector2D v1, FVector2D v2, FVector2D v3, bool isYup)
{
	const float h = isYup == true ? FVector2D::Distance((v0 + v1) / 2, (v2 + v3) / 2) : FVector2D::Distance((v1 + v2) / 2, (v0 + v3) / 2);
	const float w = (v2.X + v3.X) / 2;

	const float b1 = isYup == true ? FVector2D::Distance(v1, v2) : FVector2D::Distance(v0, v1);
	const float b2 = isYup == true ? FVector2D::Distance(v0, v3) : FVector2D::Distance(v2, v3);

	float offset = ((b1 + (2 * b1)) / (3 * (b1 + b2))) * h;
	//TODO: check this if?
	return isYup == true ? FVector2D(offset, w / 2) : FVector2D(w / 2, offset);
}
//TODO: Move too polygon math
FVector2D UHexagonMath::AverageCenteriod2D(const TArray<FVector2D>& centeriods, const int size)
{
	FVector2D centeriod = FVector2D();
	for (int i = 0; i < size; i++)
	{
		centeriod += centeriods[i];
	}

	return centeriod /= size;
}
//TODO: Move too polygon math
FVector UHexagonMath::AverageCenteriod(const TArray<FVector>&  centeriods, const  int size)
{
	FVector  centeriod = FVector();
	for (int i = 0; i < size; i++)
	{
		centeriod += centeriods[i];
	}

	return centeriod /= size;
}


FVector2D UHexagonMath::HexagonSize(float radius, bool isPointyHex)
{
	FVector2D size = isPointyHex == true ? FVector2D(FMath::Sqrt(3) * radius, 2 * radius) : FVector2D(2 * radius, FMath::Sqrt(3) * radius);
	return size;
}

float UHexagonMath::HexagonRadius(FVector2D size, bool isPointyHex)
{
	float radius = isPointyHex == true ?  size.X / FMath::Sqrt(3) : size.Y / FMath::Sqrt(3);
	return radius;
}

FVector2D UHexagonMath::HexagonSpacing(FVector2D size, bool isPointyHex)
{
	FVector2D spacing = isPointyHex == true ? FVector2D(size.X, size.Y * (3/4)) : FVector2D(size.X * (3 / 4), size.Y);
	return FVector2D();
}

FVector2D UHexagonMath::GetHexagonCorner(float radius, int sideIndex, FVector2D center, bool isPointyHex)
{
	const float angleDeg = 60 * sideIndex + ((!isPointyHex) ? 0 : 30);
	const float angleRad = PI / 180 * angleDeg;

	const float x = center.X +  (radius * FMath::Cos(angleRad));
	const float y = center.Y + (radius * FMath::Sin(angleRad));

	return {x, y};
}

float UHexagonMath::GetHexagonDegree(int sideIndex, bool isPointyHex)
{
	const float angleDeg = 60 * sideIndex + ((!isPointyHex) ? 0 : 30);
	return angleDeg;
}

float UHexagonMath::GetHexagonRad(int sideIndex, bool isPointyHex)
{
	const float angleDeg = 60 * sideIndex + ((!isPointyHex) ? 0 : 30);
	const float angleRad = PI / 180 * angleDeg;
	return angleRad;
}

FHexagonShape UHexagonMath::GetHexagonShape(FVector position, float radius, float height, bool isPointyHex)
{
	return FHexagonShape(position, radius, height, isPointyHex);
}

TArray<FVector> UHexagonMath::GetHexagonTrapezoidsCenters(const float radius, const float height, const FVector position, const bool isPointyHex, const bool isCenteriod)
{
	TArray<FVector> centers;

	auto v1 = GetHexagonCorner(radius, 0, { position.X, position.Y }, isPointyHex);
	auto v2 = GetHexagonCorner(radius, 5, { position.X, position.Y }, isPointyHex);

	const float h = FVector::Distance(position, ((FVector( v1.X, v1.Y, 0) + FVector(v2.X, v2.Y, 0)) / 2));

	const float b1 = FVector::Distance(FVector(v1.X, v1.Y, 0) , FVector(v2.X, v2.Y, 0));

	v1 = GetHexagonCorner(radius, 1, { position.X, position.Y }, isPointyHex);
	v2 = GetHexagonCorner(radius, 4, { position.X, position.Y }, isPointyHex);
	const float b2 = FVector::Distance(FVector(v1.X, v1.Y, 0), FVector(v2.X, v2.Y, 0));
	
	float offset;

	if (isCenteriod)
		offset = ((b1 + (2 * b1)) / (3 * (b1 + b2))) * h;
	else
		offset = h / 2;

	if(isPointyHex)
	{
		centers.Add({ position.X + offset, position.Y, position.Z + height});
		centers.Add({ position.X - offset, position.Y, position.Z + height});
	}
	else
	{
		centers.Add({ position.X, position.Y + offset, position.Z + height});
		centers.Add({ position.X, position.Y - offset, position.Z + height});
	}

	return centers;
}

TArray<FVector> UHexagonMath::GetHexagonRhombusCenters(float radius, float height, FVector position, bool isPointyHex)
{
	TArray<FVector> centers;

	for (size_t i = 0; i < 6; i+=2)
	{
		const FVector2D centerOffset = GetHexagonCorner(radius / 2, i, { position.X, position.Y }, isPointyHex);
		centers.Add({ centerOffset.X, centerOffset.Y, position.Z + height });
	}

	return centers;
}

TArray<FVector> UHexagonMath::GetHexagonTrianglesCenters(float radius, float height, FVector position, bool isPointyHex, const bool isCenteriod)
{
	TArray<FVector> centers;

	if (isCenteriod) 
	{

		for (size_t i = 0; i < 6; i++)
		{
			const FVector2D v1 = GetHexagonCorner(radius, (i) % 6, { position.X, position.Y }, isPointyHex);
			const FVector2D v2 = GetHexagonCorner(radius, (i + 1) % 6, { position.X, position.Y }, isPointyHex);

			const FVector2D centriod = TriangleCenteriod({ position.X, position.Y }, v1, v2);
			centers.Add(FVector(centriod.X, centriod.Y, height));
		}
	
	}
	else
	{
		for (size_t i = 0; i < 6; i++)
		{
			const FVector2D centerOffset = GetHexagonCorner(radius / 2, i, { position.X, position.Y }, !isPointyHex);
			centers.Add({ centerOffset.X, centerOffset.Y, position.Z + height });
		}
	}
	return centers;
}

FHexCubeCoordinates UHexagonMath::HexagonAdd(FHexCubeCoordinates a, FHexCubeCoordinates b)
{
	return FHexCubeCoordinates(a.Q + b.Q, a.R + b.R, a.S + b.S);
}

FHexCubeCoordinates UHexagonMath::HexagonSubtract(FHexCubeCoordinates a, FHexCubeCoordinates b)
{
	return FHexCubeCoordinates(a.Q - b.Q, a.R - b.R, a.S - b.S);
}

FHexCubeCoordinates UHexagonMath::HexagonScale(FHexCubeCoordinates a, int scale)
{
	return FHexCubeCoordinates(a.Q * scale, a.R * scale, a.S * scale);
}

FHexCubeCoordinates UHexagonMath::HexagonRotateLeft(FHexCubeCoordinates a)
{
	return FHexCubeCoordinates(-a.S, -a.Q , -a.R );
}


FHexCubeCoordinates UHexagonMath::HexagonRotateRight(FHexCubeCoordinates a)
{
	return FHexCubeCoordinates(-a.R, -a.S, -a.Q);
}

const TArray<FHexCubeCoordinates> hexagonDirections{ FHexCubeCoordinates(1, 0, -1)
												, FHexCubeCoordinates(1, -1, 0)
												, FHexCubeCoordinates(0, -1, 1)
												, FHexCubeCoordinates(-1, 0, 1)
												, FHexCubeCoordinates(-1, 1, 0)
												, FHexCubeCoordinates(0, 1, -1) };
FHexCubeCoordinates UHexagonMath::HexagonDirection(int side)
{
	return hexagonDirections[side % 6];
}

FHexCubeCoordinates UHexagonMath::HexagonNeighbor(FHexCubeCoordinates a, int side)
{
	return HexagonAdd(a, HexagonDirection(side % 6));
}

const TArray<FHexCubeCoordinates> hexagonDiagonals{ FHexCubeCoordinates(2, -1, -1)
													, FHexCubeCoordinates(1, -2, 1)
													, FHexCubeCoordinates(-1, -1, 2)
													, FHexCubeCoordinates(-2, 1, 1)
													, FHexCubeCoordinates(1, 2, -1)
													, FHexCubeCoordinates(1, 1, -2) };
FHexCubeCoordinates UHexagonMath::HexagonDiagonalNeighbor(FHexCubeCoordinates a, int side)
{
	return HexagonAdd(a, hexagonDiagonals[side % 6]);
}

int UHexagonMath::HexagonLength(FHexCubeCoordinates a)
{
	return int((FMath::Abs(a.Q) + FMath::Abs(a.R) + FMath::Abs(a.S)) / 2);
}

int UHexagonMath::HexagonDistance(FHexCubeCoordinates a, FHexCubeCoordinates b)
{
	return HexagonLength(HexagonSubtract(a, b));
}

FHexAxialCoordinates UHexagonMath::CubeToAxial(FHexCubeCoordinates cube)
{
	const int x = cube.Q;
	const int y = cube.R;
	return FHexAxialCoordinates(x, y);
}

FHexCubeCoordinates UHexagonMath::AxialToCube(FHexAxialCoordinates axial)
{
	const int q = axial.Col;
	const int r = axial.Row;
	const int s = -q - r;
	return FHexCubeCoordinates(q, r, s);
}

FHexAxialCoordinates UHexagonMath::CubeToOffsetAxial(EHexagonOffset offset, FHexCubeCoordinates cube, bool isPointyHex)
{
	if (isPointyHex)
	{
		const auto x = offset == EHexagonOffset::HEX_EVEN ? cube.Q + int((cube.R + 1 * (cube.R & 1)) / 2) : cube.Q + int((cube.R + -1 * (cube.R & 1)) / 2);
		const auto y = cube.R;
		return FHexAxialCoordinates(x, y);
	}
	else
	{
		const auto x = cube.Q;
		const auto y = offset == EHexagonOffset::HEX_EVEN ? cube.R + int((cube.Q + 1 * (cube.Q & 1)) / 2) : cube.R + int((cube.Q + -1 * (cube.Q & 1)) / 2);
		return FHexAxialCoordinates(x, y);
	}
}

FHexCubeCoordinates UHexagonMath::OffsetAxialToCube(EHexagonOffset offset, FHexAxialCoordinates axial, bool isPointyHex)
{
	if (isPointyHex)
	{
		const auto q = offset == EHexagonOffset::HEX_EVEN ? axial.Col - int((axial.Row + 1 * (axial.Row & 1)) / 2) : axial.Col - int((axial.Row + -1 * (axial.Row & 1)) / 2);
		const auto r = axial.Row;
		const auto s = -q - r;
		return FHexCubeCoordinates(q, r, s);
	}
	else
	{
		const auto q = axial.Col;
		const auto r = offset == EHexagonOffset::HEX_EVEN ? axial.Row - int((axial.Col + 1 * (axial.Col & 1)) / 2) : axial.Row - int((axial.Col + -1 * (axial.Col & 1)) / 2);;
		const auto s = -q - r;
		return FHexCubeCoordinates(q, r, s);
	}
}
