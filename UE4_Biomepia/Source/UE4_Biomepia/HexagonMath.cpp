// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonMath.h"
#include "HexagonShapeFunctions.h"
#include "Engine/Engine.h"

FVector2D UHexagonMath::GetPositionOnCircle(float rad, float radius)
{
	const float x = radius * FMath::Sin(rad);
	const float y = radius * FMath::Cos(rad);
	return {x, y};
}

FVector2D UHexagonMath::GetHexagonCorner(float radius, int sideIndex, FVector2D center, bool isPointyHex)
{
	const float angleDeg = 60 * sideIndex + ((!isPointyHex) ? 0 : 30);
	const float angleRad = PI / 180 * angleDeg;

	const float x = center.X + radius * FMath::Cos(angleRad);
	const float y = center.Y + radius * FMath::Sin(angleRad);

	return {x, y};
}

FHexagonShape UHexagonMath::GetHexagonShape(FVector position, float radius, float height, bool isPointyHex)
{
	return FHexagonShape(position, radius, height, isPointyHex);
}

TArray<FVector> UHexagonMath::GetHexagonTrapezoidsCenters(float radius, float height, FVector position, bool isPointyHex)
{
	TArray<FVector> centers;
	const auto shape = FHexagonShape(position, radius, height);

	const float h = FVector::Distance(shape.Center, ((shape.Corners[0] + shape.Corners[5]) / 2));

	//const float l = FVector::Distance(shape.Corners[0], shape.Corners[1]);
	const float b1 = FVector::Distance(shape.Corners[0], shape.Corners[5]);
	const float b2 = FVector::Distance(shape.Corners[1], shape.Corners[4]);

	const auto centeriod = ((b1 + (2 * b1)) / (3 * (b1 + b2))) * h;

	if(isPointyHex)
	{
		centers.Add({ shape.Center.X + centeriod, shape.Center.Y, shape.Center.Z });
		centers.Add({ shape.Center.X - centeriod, shape.Center.Y, shape.Center.Z });
	}
	else
	{
		centers.Add({ shape.Center.X, shape.Center.Y + centeriod, shape.Center.Z });
		centers.Add({ shape.Center.X, shape.Center.Y - centeriod, shape.Center.Z });
	}

	return centers;
}

TArray<FVector> UHexagonMath::GetHexagonRhombusCenters(float radius, float height, FVector position, bool isPointyHex)
{
	TArray<FVector> centers;
	const auto shape = FHexagonShape(position, radius, height);

	 auto centerOffset = GetHexagonCorner(radius / 2, 0, {position.X, position.Y}, isPointyHex);
	centers.Add({ centerOffset.X, centerOffset.Y, height});
	
	centerOffset = GetHexagonCorner(radius / 2, 2, { position.X, position.Y }, isPointyHex);
	centers.Add({ centerOffset.X, centerOffset.Y, height});
	
	centerOffset = GetHexagonCorner(radius / 2, 4, { position.X, position.Y }, isPointyHex);
	centers.Add({ centerOffset.X, centerOffset.Y, height});

	return centers;
}

TArray<FVector> UHexagonMath::GetHexagonTrianglesCenters(float radius, float height, FVector position, bool isPointyHex)
{
	TArray<FVector> centers;
	const auto shape = FHexagonShape(position, radius, height);

	const float h = radius;

	const float l = FVector::Distance(shape.Corners[0], shape.Corners[1]);
	const float b1 = FVector::Distance(shape.Corners[0], shape.Corners[5]);
	const float b2 = FVector::Distance(shape.Corners[1], shape.Corners[4]);

	const auto centeriod = ((b1 + (2 * b1)) / (3 * (b1 + b2))) * h;

	if (isPointyHex)
	{
		centers.Add({ shape.Center.X + centeriod, shape.Center.Y, shape.Center.Z });
		centers.Add({ shape.Center.X - centeriod, shape.Center.Y, shape.Center.Z });
	}
	else
	{
		centers.Add({ shape.Center.X, shape.Center.Y + centeriod, shape.Center.Z });
		centers.Add({ shape.Center.X, shape.Center.Y - centeriod, shape.Center.Z });
	}

	return centers;
}
