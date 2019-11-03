// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonShapeFunctions.h"

FVector UHexagonShapeFunctions::GetCenters(UPARAM(ref) FHexagonShape& shape) const
{
	return HexagonShape.GetCenter();
}

TArray<FVector> UHexagonShapeFunctions::GetCorners(UPARAM(ref) FHexagonShape& shape) const
{
	return HexagonShape.GetCorners();
}