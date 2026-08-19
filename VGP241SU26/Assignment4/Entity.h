#pragma once
#include <iostream>
#include <Vector2.h>

class Entity
{
public:
	void Initialize(const std::string& textureFilePath);
	void Update();
	void Render();
private:
	std::size_t mTextureId;
	Vector2 mPosition;
};