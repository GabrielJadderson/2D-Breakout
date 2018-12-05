#include "pch.h"

Brick::Brick(sf::Sprite sprite, sf::Vector2f pos)
{
	Sprite = sprite;
	Sprite.setPosition(pos);

	m_Size.x = Sprite.getLocalBounds().width;
	m_Size.y = Sprite.getLocalBounds().height;
	Rect = sf::FloatRect(Sprite.getPosition(), m_Size);

	//load tilemap and store its sprites in here, the sprite in the gameobject is the one being rendered.
}


Brick::~Brick()
{
}

void Brick::move(int dx, int dy) const
{
	/*
	this->sprite->move(dx, dy);

	if (this->sprite->getPosition().x > Constants::WIDTH)
		this->sprite->setPosition(Constants::WIDTH, sprite->getPosition().y);
	if (this->sprite->getPosition().y > Constants::HEIGHT)
		this->sprite->setPosition(sprite->getPosition().x, Constants::HEIGHT);
	*/
}

void Brick::OnIntersect()
{
	Sprite.setScale(0, 0);
	Sprite.setPosition(0, 0);
	Enabled(false);
}