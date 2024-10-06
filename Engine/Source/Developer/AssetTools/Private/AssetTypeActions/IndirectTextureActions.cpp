// Fill out your copyright notice in the Description page of Project Settings.


#include "IndirectTextureActions.h"
#include "Engine/IndirectTexture.h"

UClass* FIndirectTextureAssetTypeActions::GetSupportedClass() const
{
	return UIndirectTexture::StaticClass();
}

FText FIndirectTextureAssetTypeActions::GetName() const
{
	return INVTEXT("Indirect Texture");
}

FColor FIndirectTextureAssetTypeActions::GetTypeColor() const
{
	return FColor::Red;
}

uint32 FIndirectTextureAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::MaterialsAndTextures;
}
