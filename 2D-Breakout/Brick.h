#pragma once

class Brick : public GameObject
{
private:
	sf::Vector2f m_Size;
public:
	Brick(sf::Sprite sprite, sf::Vector2f pos);
	~Brick();

	void move(int dx, int dy) const;
	void OnIntersect();
};
