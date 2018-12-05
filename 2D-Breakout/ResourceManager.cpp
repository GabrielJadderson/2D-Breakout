#include "pch.h"

std::vector<sf::Font> ResourceManager::Fonts = std::vector<sf::Font>();
std::vector<sf::Text> ResourceManager::Texts = std::vector<sf::Text>();
std::map<std::string, sf::Texture*> ResourceManager::TextureMap = std::map<std::string, sf::Texture*>();
std::map<std::string, SpriteSet*> ResourceManager::SpriteSets = std::map<std::string, SpriteSet*>();


ResourceManager::ResourceManager()
{
	ResourceBlock block = ResourceSerializer::CreateResourceBlock("resources/resources.bin", DatType::Resource);
	ResourceSerializer::Stream(block);

	LoadFont("Squarebit.ttf", block);
	LoadFont("Squarebit2Px.ttf", block);

	LoadText("hello");
	LoadText("hee", GetFont(1));

	LoadTexture("breakout_pieces.png", block);
	LoadTexture("balls_8x8.png", block);
	LoadTexture("hearts_10x9.png", block);
	LoadTexture("platform_large_64x16.png", block);
	LoadTexture("platform_locked_64x20.png", block);
	LoadTexture("platform_small_32x16.png", block);
	LoadTexture("bricks_32x16.png", block);



	int width = 7;
	int height = 2;

	auto bricks = new SpriteSet(GetTexture("bricks_32x16.png"), sf::Vector2u(32, 16), width, height);
	auto platform_small = new SpriteSet(GetTexture("platform_small_32x16.png"), sf::Vector2u(32, 16), width, height);
	auto platform_locked = new SpriteSet(GetTexture("platform_locked_64x20.png"), sf::Vector2u(64, 20), width, height);
	auto platform_large = new SpriteSet(GetTexture("platform_large_64x16.png"), sf::Vector2u(64, 16), width, height);
	auto hearts = new SpriteSet(GetTexture("hearts_10x9.png"), sf::Vector2u(10, 9), width, height);
	auto balls = new SpriteSet(GetTexture("balls_8x8.png"), sf::Vector2u(8, 8), width, height);


	SpriteSets["bricks"] = bricks;
	SpriteSets["platform_small"] = platform_small;
	SpriteSets["platform_locked"] = platform_locked;
	SpriteSets["platform_large"] = platform_large;
	SpriteSets["hearts"] = hearts;
	SpriteSets["balls"] = balls;



	// define the level with an array of tile indices
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2,
		0, 1, 0, 0, 2, 0, 3, 3, 2, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

}


ResourceManager::~ResourceManager()
{
}
//================== Textures =======================
sf::Texture* ResourceManager::LoadTexture(const std::string& name, ResourceBlock& block)
{
	if (!name.empty())
	{
		sf::Texture* texture = new sf::Texture();
		auto data = ResourceSerializer::GetFromStream(name, block);
		if (texture->loadFromMemory(data.Data.data(), data.Data.size()))
		{
			//return texture;
			TextureMap.insert(std::pair<std::string, sf::Texture*>(name, texture));
			//TextureMap[name] = texture;
		}
	}
	return nullptr;
}

sf::Texture* ResourceManager::GetTexture(const std::string& name)
{
	if (!name.empty())
		return TextureMap.at(name);
	return nullptr;
}


//================== Texts =======================
void ResourceManager::LoadText(const std::string& text)
{
	sf::Text t;
	t.setFont(GetFont(0)); // font is a sf::Font
	t.setString(text);
	t.setFillColor(sf::Color::White);
	t.setStyle(sf::Text::Regular);
	Texts.push_back(t);
}
void ResourceManager::LoadText(const std::string& text, sf::Font font)
{
	sf::Text t;
	t.setFont(font); // font is a sf::Font
	t.setString(text);
	t.setFillColor(sf::Color::White);
	t.setStyle(sf::Text::Regular);
	Texts.push_back(t);
}

sf::Text ResourceManager::GetText(uint8_t index)
{
	return Texts.at(index);
}


void ResourceManager::LoadFont(const std::string& name, ResourceBlock& block)
{
	if (!name.empty())
	{
		sf::Font font;
		auto data = ResourceSerializer::GetFromStream(name, block);
		if (font.loadFromMemory(data.Data.data(), data.Data.size()))
		{
			Fonts.push_back(font);
		}
	}
}

sf::Font ResourceManager::GetFont(uint8_t index)
{
	return Fonts.at(index);
}