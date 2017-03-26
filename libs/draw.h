#pragma once
#include <SFML/Graphics.hpp>
#include <libs/map.h>
#include <libs/Entity.h>
#include <iostream>
#include <set>

void drawMap (sf::RenderWindow *window, Sprite *s_map)
{
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            if (TileMap[i][j] == ' ')  s_map->setTextureRect(IntRect(0, 0, 32, 32));
            if (TileMap[i][j] == 's')  s_map->setTextureRect(IntRect(32, 0, 32, 32));
            if ((TileMap[i][j] == '0')) s_map->setTextureRect(IntRect(64, 0, 32, 32));
            if ((TileMap[i][j] == 'f')) s_map->setTextureRect(IntRect(96, 0, 32, 32));
            if ((TileMap[i][j] == 'h')) s_map->setTextureRect(IntRect(128, 0, 32, 32));
            s_map->setPosition(j * 32, i * 32);

            window->draw(*s_map);
        }

    window->display();
}

void drawEntities (sf::RenderWindow *window, Player *p, std::set <Entity> en)
{
    window->draw (&p->sprite);

    //for (int i = en.begin(); i < en.end(); i++)
    //    window->draw ((*i)->sprite);
}
