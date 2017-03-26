#include <iostream>
#include <SFML/Graphics.hpp>
//#include <libs/Entity.h>
#include <libs/gameengine.h>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(640, 480), "");

    Clock clock;

    gameLoop lol (&window, 0);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		lol.update();
    }
}
