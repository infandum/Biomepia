// Fill out your copyright notice in the Description page of Project Settings.


#include "Texture2DHelper.h"
#include "TextureResource.h"
#include "Engine/Texture2D.h"

FColor UTexture2DHelper::GetColorFromTexture2D(UTexture2D* texture2D, const FVector2D uv)
{
	auto color = FColor::Black;

	if(texture2D == nullptr) return color;

	FTexture2DMipMap* my_mip_map = &texture2D->PlatformData->Mips[0];
	const auto formatted_image_data = static_cast<FColor*>(texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_ONLY));

	const uint32 texture_width = my_mip_map->SizeX;
	const uint32 pixel_x = uv.X * texture_width;
	const uint32 texture_height = my_mip_map->SizeY;
	const uint32 pixel_y = uv.Y * texture_height;

	if (pixel_x >= 0 && pixel_x < texture_width && pixel_y >= 0 && pixel_y < texture_height)
	{
		color = formatted_image_data[pixel_x * texture_width + pixel_y];
	}

	texture2D->PlatformData->Mips[0].BulkData.Unlock();
	
	return color;
}

float UTexture2DHelper::ColorToGreyScale(FColor color)
{
	return float((color.R + color.G + color.B) / 3.0f) / 255.0f;
}

float UTexture2DHelper::LinearColorToGreyScale(FLinearColor linearColor)
{
	return float((linearColor.R + linearColor.G + linearColor.B) / 3.0f);
}

