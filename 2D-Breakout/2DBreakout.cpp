#include <SFML/Graphics.hpp>
#include "tile_map.h"
#include "Constants.h"
#include "Game.h"
#include "resource_serializer.h"

void game_loop(sf::RenderWindow* window, game& game)
{
	while (true)
	{
		window->clear(sf::Color::White);
		game.update(constants::time_per_frame);
		//processEvents();
		game.draw();
		window->display();
	}
}


sf::RenderWindow* start_context()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	auto pwindow = new sf::RenderWindow(sf::VideoMode(constants::width, constants::height, 24), "AI", sf::Style::Default, settings);

	pwindow->setVerticalSyncEnabled(true);
	return pwindow;
	//delete(pwindow);
}

int main()
{
	new ResourceSerializer();
	/*
	//load constants
	constants ctx;

	const auto window = start_context();

	//load resources
	resource_manager resource_manager;

	game game(&resource_manager, window);
	*/
	return 0;
}