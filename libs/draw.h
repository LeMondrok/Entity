#pragma once
#include <SFML/Graphics.hpp>
#include <libs/map.h>
#include <libs/Entity.h>
#include <libs/Player.h>
#include <libs/Enemy.h>
#include <iostream>
#include <list>

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
}

void drawEntities (sf::RenderWindow *window, Player *p, std::list <Entity*> *enemies)
{
    window->draw (p->sprite);

    std::list<Entity*>::iterator it;

    for (it = enemies->begin(); it != enemies->end(); it++)
        window->draw ((*it)->sprite);
}

void draw(sf::RenderWindow *window, Sprite *s_map, Player *p, std::list <Entity*> *enemies)
{
    window->setView(view);
    window->clear();

    drawMap (window, s_map);
    drawEntities(window, p, enemies);

    window->display();
}
