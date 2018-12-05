#pragma once


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static std::vector<sf::Font> Fonts;
	static std::vector<sf::Text> Texts;
	static std::map<std::string, sf::Texture*> TextureMap;
	static std::map<std::string, SpriteSet*> SpriteSets;

	static sf::Texture* LoadTexture(const std::string& name, ResourceBlock& block);
	void LoadText(const std::string& text);
	void LoadText(const std::string& text, sf::Font font);
	void LoadFont(const std::string& name, ResourceBlock& block);

	//void LoadTileMap(const std::string& name, sf::Texture tile_set, sf::Vector2u tile_Size, const int* tiles, unsigned width, unsigned height, bool is_static);

	static sf::Texture* GetTexture(const std::string& name);
	static sf::Text GetText(uint8_t index);
	static sf::Font GetFont(uint8_t index);
};
