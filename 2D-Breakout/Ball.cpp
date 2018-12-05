#include "pch.h"

Ball::Ball()
{

	m_Size.x = this->Sprite.getLocalBounds().width;
	m_Size.y = this->Sprite.getLocalBounds().height;
	Rect = sf::FloatRect(Sprite.getPosition(), m_Size);

	//starting angle
	NewRandomAngle();
}


Ball::~Ball()
{
}

void Ball::UpdateSprite(sf::Sprite& sprite)
{
	this->Sprite = sprite;

	m_Size.x = this->Sprite.getLocalBounds().width;
	m_Size.y = this->Sprite.getLocalBounds().height;

	sf::Vector2f((Constants::width / 2.0f) - (this->Sprite.getLocalBounds().width / 2.0f), Constants::height - 25);

	sf::Vector2f Position((Constants::width / 2.0f) - (this->Sprite.getLocalBounds().width / 2.0f), Constants::height - 25);
	this->Sprite.setPosition(Position);
}


void Ball::SetSpeed(float dx)
{
	this->m_Speed = dx;
}

void Ball::SetPosition(float dx, float dy)
{
	Sprite.setPosition(dx, dy);
}

void Ball::SetDirection(float dx, float dy)
{
	this->m_Dir.x = dx;
	this->m_Dir.y = dy;
}

void Ball::NewRandomAngle()
{
	m_Angle = ((float)rand() / (float)(RAND_MAX)) * (3.14159265359 * 2.0f);
	m_Angle = 0.9f;
	m_Dir.x = cosf(m_Angle);
	m_Dir.y = sinf(m_Angle);
}

void Ball::UpdateAngle(float angle)
{
	m_Angle = angle;
	m_Dir.x = cosf(m_Angle);
	m_Dir.y = sinf(m_Angle);
}

sf::Vector2f Ball::GetPos()
{
	return Sprite.getPosition();
}

void Ball::Move(float dx)
{
	auto pos = Sprite.getPosition();


	pos.x += dx * m_Dir.x;
	pos.y += dx * m_Dir.y;
	Rect.left = pos.x;
	Rect.top = pos.y;

	Sprite.setPosition(pos);
	//std::cout << pos.x << " " << pos.y << std::endl;
}