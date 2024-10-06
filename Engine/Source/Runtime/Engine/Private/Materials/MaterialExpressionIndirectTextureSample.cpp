// Fill out your copyright notice in the Description page of Project Settings.


#include "Materials/MaterialExpressionIndirectTextureSample.h"
#include "MaterialCompiler.h"
#include "MaterialExpressionIO.h"

UMaterialExpressionIndirectTextureSample::UMaterialExpressionIndirectTextureSample()
	:TilesetTexture(nullptr)
{
	bShowOutputNameOnPin = true;
	TileIndexInput.InputName = TEXT("Tile Index");
	UVInput.InputName = TEXT("UVs");
	TilesetTilesCountInput.InputName = TEXT("Tileset Tiles Count");
	IndirectTextureResolutionInput.InputName = TEXT("Indirect Resolution");

	RGBOutput.OutputName = TEXT("RGB");
	RGBOutput.SetMask(1, 1, 1, 1, 0);

	ROutput.OutputName = TEXT("R");
	ROutput.SetMask(1, 1, 0, 0, 0);

	GOutput.OutputName = TEXT("G");
	GOutput.SetMask(1, 0, 1, 0, 0);

	BOutput.OutputName = TEXT("B");
	BOutput.SetMask(1, 0, 0, 1, 0);

	AOutput.OutputName = TEXT("A");
	AOutput.SetMask(1, 0, 0, 0, 1);

	RGBAOutput.OutputName = TEXT("RGBA");
	RGBAOutput.SetMask(1, 1, 1, 1, 1);
}

TArray<FExpressionOutput>& UMaterialExpressionIndirectTextureSample::GetOutputs()
{
	Outputs.Reset();
	Outputs.Add(RGBOutput);
	Outputs.Add(ROutput);
	Outputs.Add(GOutput);
	Outputs.Add(BOutput);
	Outputs.Add(AOutput);
	Outputs.Add(RGBAOutput);
	return Outputs;
}

int32 UMaterialExpressionIndirectTextureSample::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex)
{
	if (TilesetTexture == nullptr)
	{
		return Compiler->Errorf(TEXT("Indirect Texture is nullptr!"));
	} 
	else if (!TileIndexInput.Expression || !UVInput.Expression || !TilesetTilesCountInput.Expression || !IndirectTextureResolutionInput.Expression)
	{
		return Compiler->Errorf(TEXT("All input should be linked."));
	}

	int32 TilesetTextureReferenceIndex = Compiler->Texture(TilesetTexture, EMaterialSamplerType::SAMPLERTYPE_Color);
	int32 UV = CalculateUV(Compiler);

	return Compiler->TextureSample(TilesetTextureReferenceIndex, UV, EMaterialSamplerType::SAMPLERTYPE_Color);
}

UTexture* UMaterialExpressionIndirectTextureSample::GetReferencedTexture() const
{
	if (TilesetTexture != nullptr)
	{
		return TilesetTexture;
	}

	return nullptr;
}

bool UMaterialExpressionIndirectTextureSample::CanReferenceTexture() const
{
	return TilesetTexture != nullptr;
}

void UMaterialExpressionIndirectTextureSample::GetCaption(TArray<FString>& OutCaptions) const
{
	OutCaptions.Add(TEXT("IndirectTextureSample"));
}

int32 UMaterialExpressionIndirectTextureSample::CalculateUV(FMaterialCompiler* Compiler)
{
	/// <summary>
	/// Calculate and choose which tiles referenced by TileIndex
	/// </summary>
	int32 TilesetTilesCount = TilesetTilesCountInput.Compile(Compiler);
	int32 TilesetTilesColumnNum = Compiler->ComponentMask(TilesetTilesCount, 1, 0, 0, 0);
	int32 TileIndex = TileIndexInput.Compile(Compiler);

	int32 X = Compiler->Fmod(TileIndex, TilesetTilesColumnNum);
	int32 Y = Compiler->Floor(Compiler->Div(TileIndex, TilesetTilesColumnNum));

	int32 TileSteps = Compiler->Div(Compiler->Constant(1.f), TilesetTilesCount);

	int32 TileX = Compiler->Mul(X, Compiler->ComponentMask(TileSteps, 1, 0, 0, 0));
	int32 TileY = Compiler->Mul(Y, Compiler->ComponentMask(TileSteps, 0, 1, 0, 0));
	int32 TileUV = Compiler->AppendVector(Compiler->ComponentMask(TileX, 1, 0, 0, 0), Compiler->ComponentMask(TileY, 0, 1, 0, 0));

	/// <summary>
	/// Calculate UV in tileset texture
	/// </summary>
	int32 UV = UVInput.Compile(Compiler);
	int32 IndirectTextureResolution = IndirectTextureResolutionInput.Compile(Compiler);
	int32 UVOffsetInIndirectTexture = Compiler->Fmod(UV, Compiler->Div(Compiler->Constant(1.f), IndirectTextureResolution));
	int32 UVOffset = Compiler->Mul(Compiler->Mul(UVOffsetInIndirectTexture, IndirectTextureResolution), TileSteps);

	return Compiler->Add(TileUV, UVOffset);
}
