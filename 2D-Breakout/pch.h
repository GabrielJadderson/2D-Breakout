// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here


//std
#include <fstream>
#include <iostream>
#include <thread>
#include <cstdint>
#include <cstdlib>

#include <vector>
#include <map>
#include <array>

#include <memory>
//#include <type_traits>
#include <iomanip>

//libs
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Config.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

//internal
#include "BenchTimer.h"
#include "Util.h"
#include "SpriteSet.h"
#include "Resource.h"
#include "GameObject.h"
#include "Ball.h"
#include "Brick.h"
#include "Platform.h"
#include "Health.h"
#include "ResourceManager.h"
#include "ResourceLoader.h"
#include "ResourceSerializer.h"
#include "Movement.h"

#include "Constants.h"
#include "Game.h"

#endif //PCH_H
