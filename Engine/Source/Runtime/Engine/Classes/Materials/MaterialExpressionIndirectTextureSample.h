// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "MaterialExpressionIndirectTextureSample.generated.h"

/**
 * 
 */
UCLASS()
class UMaterialExpressionIndirectTextureSample : public UMaterialExpression
{
	GENERATED_BODY()
	
public:
	UMaterialExpressionIndirectTextureSample();
	virtual TArray<FExpressionOutput>& GetOutputs() override;
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual UTexture* GetReferencedTexture() const override;
	virtual bool CanReferenceTexture() const override;
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;
private:
	// Helper function calculating tile UV
	int32 CalculateUV(class FMaterialCompiler* Compiler);
	
public:

	UPROPERTY(meta = (RequiredInput = "true"), EditAnywhere, BlueprintReadWrite, Category = "IndirectTexture")
	UTexture2D* TilesetTexture;

	UPROPERTY(EditAnywhere, Category = "Indirect Texture")
	FExpressionInput TileIndexInput;

	UPROPERTY(EditAnywhere, Category = "Indirect Texture")
	FExpressionInput UVInput;

	UPROPERTY(EditAnywhere, Category = "Indirect Texture")
	FExpressionInput TilesetTilesCountInput;

	UPROPERTY(EditAnywhere, Category = "Indirect Texture")
	FExpressionInput IndirectTextureResolutionInput;

	UPROPERTY()
	FExpressionOutput RGBOutput;

	UPROPERTY()
	FExpressionOutput ROutput;

	UPROPERTY()
	FExpressionOutput GOutput;

	UPROPERTY()
	FExpressionOutput BOutput;

	UPROPERTY()
	FExpressionOutput AOutput;

	UPROPERTY()
	FExpressionOutput RGBAOutput;
};
