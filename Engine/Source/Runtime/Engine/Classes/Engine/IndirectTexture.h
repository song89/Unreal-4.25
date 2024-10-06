// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IndirectTexture.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TEST_API UIndirectTexture : public UObject
{
	GENERATED_BODY()

	public:
	UIndirectTexture();

	UFUNCTION(CallInEditor, Category = "Indirect Texture")
	void CreateIndirectTexture();

public:
	UPROPERTY(VisibleAnywhere, Category = "Indirect Texture")
	UTexture2D* IndirectTexture;

	UPROPERTY(EditAnywhere, Category = "Indirect Texture")
	UTexture2D* TilesetTexture;

	UPROPERTY(EditAnywhere, Category = "Indirect Texture")
	FIntPoint TilesetTilesCount;

	UPROPERTY(EditAnywhere, Category = "Indirect Texture")
	FIntPoint IndirectTextureResolution;
};
