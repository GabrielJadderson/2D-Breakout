// 2D-Breakout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"


/*
void GameLoop(sf::RenderWindow* window, Game& game)
{
	while (true)
	{
		window->clear(sf::Color::White);
		game.Update(Constants::time_per_frame);
		//processEvents();
		game.Draw();
		window->display();
	}
}
*/


sf::RenderWindow* StartContext()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	auto pwindow = new sf::RenderWindow(sf::VideoMode(Constants::width, Constants::height, 24), "2D-Breakout", sf::Style::Default, settings);

	pwindow->setVerticalSyncEnabled(true);
	pwindow->setFramerateLimit(60);

	return pwindow;
	//delete(pwindow);
}



int main()
{
	new ResourceSerializer();


	//load constants
	Constants ctx;

	const auto window = StartContext();

	//load resources
	ResourceManager resource_manager;

	Game Game(&resource_manager, window);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file