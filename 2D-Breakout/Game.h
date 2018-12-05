#pragma once


class Game
{
public:
	Game(ResourceManager* rm, sf::RenderWindow* window);
	~Game();

	void LoadBricks(unsigned int x, unsigned int y, int spacing, int x_offset, int y_offset);
	void LoadHealth(unsigned int x, unsigned int y, int spacing, int x_offset, int y_offset);

	void Update(float elapsedTime);
	void Draw();
	void GameLoop();

	std::vector<Brick> bricks;
	std::vector<Brick> inactiveBricks;
	std::vector<Brick> activeBricks;

	std::vector<Health> health;
	Ball ball;
	Platform platform;

	float deltaTime;
	float elapsedTime;

private:
	ResourceManager* _res;
	sf::RenderWindow* _win;
	uint8_t _brick_count = 0;
	uint8_t _health_count = 0;
	sf::Time _delta_time;
	sf::Time _elapsedTime;
	sf::Clock _delta_clock;
	sf::Clock _elapsed_clock;
	sf::Event m_Event;
};
