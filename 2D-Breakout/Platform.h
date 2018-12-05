#pragma once

class Platform : public GameObject
{
public:
	float m_Speed;
	sf::Vector2f m_Size;
public:
	Platform();
	~Platform();

	void UpdateSprite(sf::Sprite& sprite);
	sf::Vector2f GetPos();
	void Move(float dx, float elapsedTime);
	void MoveLeft(float elapsedTime);
	void MoveRight(float elapsedTime);
	void Interpolate(float dx, float elapsedTime);
	void SetSpeed(float x);
};
