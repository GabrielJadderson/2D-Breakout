#include "pch.h"

SpriteSet::SpriteSet()
{
}

SpriteSet::SpriteSet(sf::Texture* texture, sf::Vector2u tileSize, unsigned int width, unsigned int height) :
	Texture(texture), TileSize(tileSize), Width(width), Height(height)
{
	Sprites = {};
	auto ts = texture->getSize();

	for (unsigned int i = 0; i < ts.x / tileSize.x; ++i)
		for (unsigned int j = 0; j < ts.y / tileSize.y; ++j)
		{
			auto sprite = sf::Sprite();
			sprite.setTexture(*texture);
			sprite.setTextureRect(sf::IntRect(tileSize.x*i, tileSize.y*j, tileSize.x, tileSize.y));
			sprite.setPosition(0, 0);
			Sprites.push_back(sprite);
		}

	std::cout << "Loaded SpriteSet " << tileSize.x << "x" << tileSize.y << std::endl;
}

SpriteSet::~SpriteSet()
{
}