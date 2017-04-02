#include <iostream>
#include <SFML/Graphics.hpp>
//#include <libs/Entity.h>
#include <libs/gameengine.h>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(640, 480), "");

    view.reset(FloatRect(0, 0, 640, 480));

    Clock clock;

    Image heroImage;
    heroImage.loadFromFile("images/b.gif");

    Player player (heroImage, 750, 500, 40, 30, "gamer");

    gameLoop lol (&window, 0, &player);

    Enemy E(heroImage, 750, 500, 40, 30, "gameraa");

    lol.enemies.push_back(&E);

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

        Event event;

        while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		lol.update(time);
    }
}
