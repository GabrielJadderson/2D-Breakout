#pragma once
class SpriteSet
{
public:
	std::vector<sf::Sprite> Sprites;
	sf::Texture* Texture;
	sf::Vector2u TileSize;
	unsigned int Width = 0;
	unsigned int Height = 0;
private:

public:
	SpriteSet();
	SpriteSet(sf::Texture* texture, sf::Vector2u tileSize, unsigned int width, unsigned int height);
	~SpriteSet();
};
