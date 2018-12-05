#pragma once


class GameObject
{
public:
	GameObject();
	~GameObject();

	sf::Vector2f Scale;
	sf::Sprite Sprite;
	sf::FloatRect Rect;
	bool isEnabled = true;

	void Draw(sf::RenderWindow* window);
	bool Contains(GameObject& other) const;
	bool Contains(sf::Vector2f& other) const;
	bool Contains(sf::Vector2i& other);

	void Enabled(bool value);


};
