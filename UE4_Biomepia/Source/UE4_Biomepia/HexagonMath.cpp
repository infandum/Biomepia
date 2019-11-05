// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonMath.h"
#include "Engine/Engine.h"

FVector2D UHexagonMath::GetPositionOnCircle(float rad, float radius, FVector2D center)
{
	const float x = radius * FMath::Sin(rad);
	const float y = radius * FMath::Cos(rad);
	return { center.X + x, center.Y + y};
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
	//auto shape = FHexagonShape(position, radius, height);

	auto v1 = GetHexagonCorner(radius, 0, { position.X, position.Y }, isPointyHex);
	auto v2 = GetHexagonCorner(radius, 5, { position.X, position.Y }, isPointyHex);
	const float h = FVector::Distance(position, ((FVector( v1.X, v1.Y, 0) + FVector(v2.X, v2.Y, 0)) / 2));

	//const float l = FVector::Distance(shape.Corners[0], shape.Corners[1]);
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
	
	auto centerOffset = GetHexagonCorner(radius / 2, 0, {position.X, position.Y}, isPointyHex);
	centers.Add({ centerOffset.X, centerOffset.Y, position.Z + height });
	
	centerOffset = GetHexagonCorner(radius / 2, 2, { position.X, position.Y }, isPointyHex);
	centers.Add({ centerOffset.X, centerOffset.Y, position.Z + height});
	
	centerOffset = GetHexagonCorner(radius / 2, 4, { position.X, position.Y }, isPointyHex);
	centers.Add({ centerOffset.X, centerOffset.Y, position.Z + height});

	return centers;
}

TArray<FVector> UHexagonMath::GetHexagonTrianglesCenters(float radius, float height, FVector position, bool isPointyHex)
{
	TArray<FVector> centers;

	auto v1 = GetHexagonCorner(radius, 0, { position.X, position.Y }, isPointyHex);
	auto v2 = GetHexagonCorner(radius, 5, { position.X, position.Y }, isPointyHex);
	const float h = radius;

	//const float l = FVector::Distance(shape.Corners[0], shape.Corners[1]);
	//const float b1 = FVector::Distance(shape.Corners[0], shape.Corners[5]);
	//const float b2 = FVector::Distance(shape.Corners[1], shape.Corners[4]);

	//const auto centeriod = ((b1 + (2 * b1)) / (3 * (b1 + b2))) * h;

	//if (isPointyHex)
	//{
	//	centers.Add({ shape.Center.X + centeriod, shape.Center.Y, shape.Center.Z });
	//	centers.Add({ shape.Center.X - centeriod, shape.Center.Y, shape.Center.Z });
	//}
	//else
	//{
	//	centers.Add({ shape.Center.X, shape.Center.Y + centeriod, shape.Center.Z });
	//	centers.Add({ shape.Center.X, shape.Center.Y - centeriod, shape.Center.Z });
	//}

	return centers;
}
