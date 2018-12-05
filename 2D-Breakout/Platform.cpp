#include "pch.h"


Platform::Platform()
{
	m_Size.x = Sprite.getLocalBounds().width;
	m_Size.y = Sprite.getLocalBounds().height;
	Rect = sf::FloatRect(Sprite.getPosition(), m_Size);

	//set initial platform position
	sf::Vector2f((Constants::width / 2.0f) - (Sprite.getLocalBounds().width / 2.0f), Constants::height - 25);
	sf::Vector2f Position((Constants::width / 2.0f) - (Sprite.getLocalBounds().width / 2.0f), Constants::height - 25);
	Sprite.setPosition(Position);
}

void Platform::UpdateSprite(sf::Sprite& sprite)
{
	Sprite = sprite;
	sf::Vector2f((Constants::width / 2.0f) - (Sprite.getLocalBounds().width / 2.0f), Constants::height - 25);
	sf::Vector2f Position((Constants::width / 2.0f) - (Sprite.getLocalBounds().width / 2.0f), Constants::height - 25);
	Sprite.setPosition(Position);
}

sf::Vector2f Platform::GetPos()
{
	return Sprite.getPosition();
}

void Platform::Move(float dx, float elapsedTime)
{
	sf::Vector2f Position = Sprite.getPosition();
	if (Position.x >= Constants::width - 70)
	{
		Position.x -= 1;
		Sprite.setPosition(Position.x, Position.y);
	}
	else if (Position.x <= 8) {
		Position.x += 1;
		Sprite.setPosition(Position.x, Position.y);
	}
	else
	{
		float ddx = dx * elapsedTime;
		Position.x += ddx;
		Rect.left = (Rect.width / 2) + Position.x;
		Rect.top = (Rect.height / 2) + Position.y;
		Sprite.move(ddx, 0);
	}
}

void Platform::MoveLeft(float elapsedTime)
{
	Move(-m_Speed, elapsedTime);
}


void Platform::MoveRight(float elapsedTime)
{
	Move(m_Speed, elapsedTime);
}

void Platform::Interpolate(float dx, float elapsedTime)
{
	sf::Vector2f Position = Sprite.getPosition();
	if (Position.x >= Constants::width - 70)
	{
		Position.x -= 1;
		Sprite.setPosition(Position.x, Position.y);
	}
	else if (Position.x <= 8) {
		Position.x += 1;
		Sprite.setPosition(Position.x, Position.y);
	}
	else
	{
		float ddx = lerp(Position.x, dx, elapsedTime / 2);
		Position.x += ddx;
		Rect.left = (Rect.width / 2) + Position.x;
		Rect.top = (Rect.height / 2) + Position.y;
		Sprite.move(ddx, 0);
	}
}

void Platform::SetSpeed(float x)
{
	this->m_Speed = x;
}


Platform::~Platform()
{
}