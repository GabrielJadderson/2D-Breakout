#include "pch.h"

const sf::Time Constants::time_per_frame = sf::seconds(1.f / Constants::fps);

sf::Vector2i Constants::MousePosition = sf::Vector2i(0, 0);

Constants::Constants()
{

}

Constants::~Constants()
{
	//clean up
}