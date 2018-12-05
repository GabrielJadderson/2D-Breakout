#include "pch.h"


Game::Game(ResourceManager* rm, sf::RenderWindow* window)
{
	this->_res = rm;
	this->_win = window;

	LoadBricks(27, 25, 5, 15, 50);
	LoadHealth(3, 1, 5, Constants::width - 55, 10);

	auto ballSet = ResourceManager::SpriteSets["balls"];

	ball.Sprite = (ballSet->Sprites.at(0));
	ball.Sprite.setPosition(10, 10);

	auto platformSet = ResourceManager::SpriteSets["platform_large"];

	platform.UpdateSprite(platformSet->Sprites.at(0));
	platform.SetSpeed(500.0f);
	//BEGIN
	GameLoop();
}

void Game::LoadBricks(unsigned int x, unsigned int y, int spacing, int x_offset, int y_offset)
{
	if (!ResourceManager::SpriteSets.empty()) {
		bricks.reserve(x*y);
		inactiveBricks.reserve(x*y);
		auto brickSet = ResourceManager::SpriteSets["bricks"];
		for (unsigned i = 0; i < x; i++)
		{
			for (unsigned j = 0; j < y; j++)
			{
				sf::Sprite s = brickSet->Sprites.at(rand() % brickSet->Sprites.size());
				sf::Vector2f pos;
				pos.x = (float(i)*(float(brickSet->TileSize.x) + spacing) + x_offset);
				pos.y = (float(j)*(float(brickSet->TileSize.y) + spacing)) + y_offset;
				Brick b(s, pos);
				bricks.push_back(b);
			}
		}
	}
}


void Game::LoadHealth(unsigned int x, unsigned int y, int spacing, int x_offset, int y_offset)
{
	if (!ResourceManager::SpriteSets.empty()) {

		auto heartSet = ResourceManager::SpriteSets["hearts"];
		for (unsigned i = 0; i < x; i++)
		{
			for (unsigned j = 0; j < y; j++)
			{
				sf::Sprite s = heartSet->Sprites.at(0);

				s.setPosition((float(i)*(float(heartSet->TileSize.x) + spacing) + x_offset), (float(j)*(float(heartSet->TileSize.y) + spacing)) + y_offset);

				Health b(s);
				health.push_back(b);
			}
		}
	}
}


inline float Dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

float fSpeed = 5.0f;

void Game::Update(float elapsedTime)
{
	// check all the window's events that were triggered since the last iteration of the loop
	while (_win->pollEvent(m_Event))
	{
		// "close requested" event: we close the window
		if (m_Event.type == sf::Event::Closed)
		{
			_win->close();
			exit(0);
		}
	}

	//get mouse position
	Constants::MousePosition = sf::Mouse::getPosition(*_win);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		platform.MoveLeft(elapsedTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		platform.MoveRight(elapsedTime);


	if (platform.Contains(Constants::MousePosition))
	{
		platform.Enabled(false);
		std::cout << "yes\n";
	}
	if (ball.Contains(Constants::MousePosition))
	{
		platform.Enabled(false);
		std::cout << "no\n";
	}


	if (platform.Contains(ball))
	{
		//ball.NewRandomAngle();
		//ball.SetDirection()
		std::cout << "yes\n";
	}

	if (ball.Contains(platform))
	{
		sf::Vector2f pos = ball.Sprite.getPosition();

		//ball.SetDirection()
		std::cout << "no\n";
	}

	sf::Vector2f pos = ball.GetPos();
	sf::Vector2f pPos = platform.GetPos();
	if (pos.x > Constants::width || pos.x < 0)
		ball.m_Dir.x *= -1; // horiz wall hit
	if (pos.y > Constants::height || pos.y < 0)
		ball.m_Dir.y *= -1; // vert wall hit

	if (pos.x >= pPos.x && pos.x <= pPos.x + platform.m_Size.x && pos.y >= pPos.y && pos.y <= pPos.y + platform.m_Size.y) {
		// paddle hit
		float paddleCenter = pPos.y + (platform.m_Size.y / 2);
		float d = paddleCenter - pos.y;
		ball.m_Dir.y += d * -0.1; // here's the trick
		ball.m_Dir.x *= -1;
	}

	ball.Move(elapsedTime * 1000.0f);

	if (platform.Contains(ball))
	{
		pos.y = pPos.y - platform.Sprite.getGlobalBounds().height;
		ball.m_Dir.y *= -1;

		// determine X
		ball.m_Dir.x = 1 - 2 * (pPos.x - pos.x) / (platform.Sprite.getGlobalBounds().width / 2);
	}

	if (!bricks.empty())
	{
		for (int i = 0; i < bricks.size(); ++i)
		{
			if (bricks[i].Contains(Constants::MousePosition))
			{
				bricks[i].Enabled(false);
			}

			if (bricks[i].Contains(ball))
			{
				ball.m_Dir.x *= 1;
				ball.m_Dir.y *= 1;
				//ball.UpdateAngle(ball.m_Angle + 2.2);
				//brick.Sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
				bricks[i].Enabled(false);
			}
		}
	}
	else
	{
		//Win!
	}


	if (_brick_count < 1)
	{
		//win
	}

	if (_health_count < 1)
	{
		//loose
	}

}

//loop
void Game::Draw()
{

	platform.Draw(_win);

	ball.Draw(_win);

	if (!bricks.empty())
		for (auto& brick : bricks)
		{
			brick.Draw(_win);
		}

	if (!health.empty())
		for (auto& h : health)
		{
			h.Draw(_win);
		}

}

float lastTime = 0;

void Game::GameLoop()
{
	_win->setActive(true);
	sf::Font font;
	font.loadFromFile("resources/fonts/Squarebit.ttf");
	while (true)
	{
		_win->clear(sf::Color::White);

		elapsedTime = _elapsed_clock.restart().asSeconds();
		float fps = 1.f / (elapsedTime - lastTime);
		lastTime = elapsedTime;

		Update(elapsedTime);

		Draw();

		_win->display();

	}
}



Game::~Game()
{

	_elapsedTime = _elapsed_clock.restart();
	elapsedTime = _elapsedTime.asMilliseconds();

	//clean up resoruce manager
	//clean up window
	//clean up itself.
}