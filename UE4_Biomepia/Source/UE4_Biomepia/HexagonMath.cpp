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
FVector2D UHexagonMath::GetTriangleCenteriod(FVector2D v0, FVector2D v1, FVector2D v2)
{
	float x = (v0.X + v1.X + v2.X) / 3;
	float y = (v0.Y + v1.Y + v2.Y) / 3;
	return FVector2D(x, y);
}
//TODO: Move too polygon math
FVector2D UHexagonMath::GetAverageCenteriod2D(const TArray<FVector2D>& centeriods, const unsigned int size)
{
	FVector2D centeriod = FVector2D();
	for (int i = 0; i < size; i++)
	{
		centeriod += centeriods[i];
	}

	return centeriod /= size;
}
//TODO: Move too polygon math
FVector UHexagonMath::GetAverageCenteriod(const TArray<FVector>&  centeriods, const unsigned int size)
{
	FVector  centeriod = FVector();
	for (int i = 0; i < size; i++)
	{
		centeriod += centeriods[i];
	}

	return centeriod /= size;
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

			const FVector2D centriod = GetTriangleCenteriod({ position.X, position.Y }, v1, v2);
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

