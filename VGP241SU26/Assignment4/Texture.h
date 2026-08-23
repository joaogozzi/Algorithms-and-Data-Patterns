#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& filePath);
	Texture();

	void Print() const;
private:
	std::string mFilePath;
};