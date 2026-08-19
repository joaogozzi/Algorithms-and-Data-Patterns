#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& filePath);
	Texture();

	void Print();
private:
	std::string mFilePath;
};