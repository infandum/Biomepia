// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Texture2DHelper.generated.h"


class UTexture2D;
/**
 * 
 */
UCLASS()
class UE4_BIOMEPIA_API UTexture2DHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Helper")
		static FColor GetColorFromTexture2D(UTexture2D* texture2D, FVector2D uv);

		UFUNCTION(BlueprintPure, Category = "Helper")
		static float ColorToGreyScale(FColor color);

		UFUNCTION(BlueprintPure, Category = "Helper")
		static float LinearColorToGreyScale(FLinearColor linearColor);
};
