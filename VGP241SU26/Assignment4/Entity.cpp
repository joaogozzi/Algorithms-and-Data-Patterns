#include "Entity.h"
#include "TextureManager.h"

Entity::Entity()
	: mTextureId(0),
	mPosition{ 0.0f, 0.0f }
{
}

void Entity::Initialize(const std::string& textureFilePath)
{
	mTextureId = TextureManager::Instance().LoadTexture(textureFilePath);

	mPosition.x = std::rand() % 401 - 200;
	mPosition.y = std::rand() % 401 - 200;
}

void Entity::Update()
{
	mPosition.x = std::rand() % 401 - 200;
	mPosition.y = std::rand() % 401 - 200;
}

void Entity::Render() const
{
	Texture& texture = TextureManager::Instance().GetTexture(mTextureId);

	texture.Print();

	std::cout << "Position: (" << mPosition.x << ", " << mPosition.y << ")" << "\n";
}

float Entity::GetDistanceFromOrigin() const
{
	return (mPosition.x * mPosition.x) + (mPosition.y * mPosition.y);
}