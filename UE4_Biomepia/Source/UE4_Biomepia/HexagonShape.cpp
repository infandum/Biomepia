// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonShape.h"
#include "HexagonMath.h"

//FHexagonShape::FHexagonShape(): Radius(0), IsPointyHexagon(false)
//{
//	FHexagonShape(FVector(0, 0, 0), true);
//}
//
//FHexagonShape::FHexagonShape(FVector position, bool isPointyHex): Radius(0), IsPointyHexagon(false)
//{
//	FHexagonShape(position, 100.0f, 0.0f, isPointyHex);
//}
//
//FHexagonShape::FHexagonShape(FVector position, float radius, float height, bool isPointyHex): Radius(0),
//                                                                                              IsPointyHexagon(false)
//{
//	Center = {position.X, position.Y, height};
//
//	FVector2D corner = UHexagonMath::GetHexagonCorner(radius, 0, {position.X, position.Y}, isPointyHex);
//	Corners.Add({corner.X, corner.Y, Center.Z});
//
//	corner = UHexagonMath::GetHexagonCorner(radius, 0, {position.X, position.Y}, isPointyHex);
//	Corners.Add({corner.X, corner.Y, Center.Z});
//
//	corner = UHexagonMath::GetHexagonCorner(radius, 1, {position.X, position.Y}, isPointyHex);
//	Corners.Add({corner.X, corner.Y, Center.Z});
//
//	corner = UHexagonMath::GetHexagonCorner(radius, 2, {position.X, position.Y}, isPointyHex);
//	Corners.Add({corner.X, corner.Y, Center.Z});
//
//	corner = UHexagonMath::GetHexagonCorner(radius, 3, {position.X, position.Y}, isPointyHex);
//	Corners.Add({corner.X, corner.Y, Center.Z});
//
//	corner = UHexagonMath::GetHexagonCorner(radius, 4, {position.X, position.Y}, isPointyHex);
//	Corners.Add({corner.X, corner.Y, Center.Z});
//
//	corner = UHexagonMath::GetHexagonCorner(radius, 5, {position.X, position.Y}, isPointyHex);
//	Corners.Add({corner.X, corner.Y, Center.Z});
//}
//
//FVector GetCenter()
//{
//	return HexagonShape.GetCenter();
//}
//
//TArray<FVector> GetCorners()
//{
//	return HexagonShape.GetCorners();
//}