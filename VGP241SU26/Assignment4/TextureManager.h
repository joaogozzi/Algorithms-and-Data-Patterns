#pragma once
#include <iostream>
#include "Texture.h"
#include <UnorderedMap.h>

class TextureManager
{
public:
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    static TextureManager& Instance();

    std::size_t LoadTexture(const std::string& filePath);

    Texture& GetTexture(size_t textureId);

private:
    TextureManager() = default;

    UnorderedMap<std::size_t, Texture> mTextures;
};