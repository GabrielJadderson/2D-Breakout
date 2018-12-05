#pragma once

class Ball : public GameObject
{
public:
	float m_Angle;
	float m_Speed;
	sf::Vector2f m_Dir;
	sf::Vector2f m_Size;

public:
	Ball();
	~Ball();

	void UpdateSprite(sf::Sprite& sprite);
	void SetSpeed(float x);
	void SetPosition(float x, float y);
	void SetDirection(float dx, float dy);
	void NewRandomAngle();
	void UpdateAngle(float angle);
	sf::Vector2f GetPos();
	void Move(float dx, float dy);
	void Move(float dx);
};
