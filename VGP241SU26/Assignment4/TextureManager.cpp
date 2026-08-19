#include "TextureManager.h"
#include <Global.h>

TextureManager::TextureManager()
{
}

TextureManager& TextureManager::Instance()
{
	static TextureManager instance;
	return instance;
}

std::size_t TextureManager::LoadTexture(const std::string& filePath)
{
	std::size_t uniqueId = Global::HashFunction(filePath);

	mTextures[uniqueId] = filePath;

	return uniqueId;
}
