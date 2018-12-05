#pragma once



class Constants
{
public:
	Constants();
	~Constants();
	static const int width = 1024;
	static const int height = 768;

	constexpr static const float fps = 60.0f;
	static const sf::Time time_per_frame;

	static sf::Vector2i MousePosition;

};
