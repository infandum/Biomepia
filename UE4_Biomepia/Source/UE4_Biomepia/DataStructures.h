// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.generated.h"

USTRUCT(BlueprintType)
struct FHexTileData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D LocationIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D HeightUV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Elevation;

	//Constructor
	FHexTileData()
	{
		Name = "Hex: 0,0";
		Transform = FTransform();
		LocationIndex = FVector2D(0, 0);
		HeightUV = FVector2D(0, 0);
		Elevation = 0.0f;
	}

	FHexTileData(FTransform transform, FVector2D index, FVector2D uv, float elevation = 0.f)
	{
		Name = "Hex:" + FString::SanitizeFloat(index.X) + "," + FString::SanitizeFloat(index.Y);
		Transform = transform;
		LocationIndex = index;
		HeightUV = uv;
		Elevation = elevation;
	}

	void SetHeight(const float height)
	{
		Elevation = height;
	}

	void SetElevation(const float elevation)
	{
		Elevation = elevation;
	}

	float GetElevation() const
	{
		return Elevation;
	}
};

//FHexTileData MyStruct;
//
//UFUNCTION(BlueprintCallable, Category = "Hexagon Data")
//void SetHexTileData(FTransform transform, FVector2D index, FVector2D uv, float elevation = 0.f);

//UFUNCTION(BlueprintPure, Category = "Hexagon Data")
//void FHexTileData(FTransform transform, FVector2D index, FVector2D uv, float elevation = 0.f);

////source file
//void MyClass::SetInteger(const int32 NewInteger)
//{
//	MyStruct.SetInt(NewInteger);
//}
//
//int32 MyClass::GetInteger() const
//{
//	return MyStruct.GetInt();
//}