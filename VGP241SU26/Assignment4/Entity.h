#pragma once
#include <iostream>
#include <Vector2.h>

class Entity
{
public:
	Entity();

	void Initialize(const std::string& textureFilePath);
	void Update();
	void Render() const;

	float GetDistanceFromOrigin() const;
private:
	std::size_t mTextureId;
	Vector2 mPosition;
};