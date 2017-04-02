#pragma once
#include <libs/draw.h>
#include <libs/Entity.h>
#include <libs/Player.h>
#include <libs/Enemy.h>
#include <list>

using namespace sf;

class gameLoop
{
public:
    std::list <Entity*> enemies;
    Sprite s_map;
    Image map_image;
    Texture map;

    gameLoop (RenderWindow *Window, bool choose, Player *P)
    {
        window = Window;

        map_image.loadFromFile("images/map.png");

        map.loadFromImage(map_image);

        s_map.setTexture(map);

        p = P;
    }

    update(float time)
    {
		p->update(time, &enemies);

        for (std::list<Entity*>::iterator it = enemies.begin(); it != enemies.end(); it++)
            (*it)->update(time, &enemies);

        draw(window, &s_map, p, &enemies);
    }

private:
    RenderWindow *window;

    Player *p;

    Entity *E;
};
