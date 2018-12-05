#include "pch.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}


void GameObject::Draw(sf::RenderWindow* window)
{
	if (isEnabled)
	{
		window->draw(this->Sprite);
	}
}


bool GameObject::Contains(GameObject& other) const
{
	if (isEnabled)
		return Rect.contains(other.Sprite.getPosition());
	return false;
}

bool GameObject::Contains(sf::Vector2f& other) const
{
	if (isEnabled)
		return Rect.contains(other);
	return false;
}

bool GameObject::Contains(sf::Vector2i& other)
{
	if (isEnabled)
		return Rect.contains(sf::Vector2f(other));
	return false;
}

void GameObject::Enabled(bool value)
{
	if (value == false)
	{
		Scale = Sprite.getScale();
		Sprite.setScale(0, 0);
		isEnabled = false;
	}
	else
	{
		Sprite.setScale(Scale);
		isEnabled = true;

	}
}