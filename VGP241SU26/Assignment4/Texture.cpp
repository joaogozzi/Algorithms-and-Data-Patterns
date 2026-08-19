#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string& filePath)
	: mFilePath(filePath)
{}

Texture::Texture()
{}

void Texture::Print()
{
	std::cout << "Rendering <" << mFilePath << ">\n";
}