#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <libs/map.h>
#include <libs/view.h>
#include <list>

unsigned int ident = 0;

class Entity
{
public:
    float vx, vy, x, y, speed;
    int health, w, h;
    bool life, onGround;
    unsigned int num;

    enum { unfr, fr, ubul, frbul} type;

    sf::Texture texture;
	sf::Sprite sprite;
	std::string name;

    Entity (sf::Image *image, float X, float Y, int W, int H, std::string Name)
    {
        num = ident;
        ident++;
        x = X;
        y = Y;
        w = W;
        h = H;

        speed = 0;

        name = Name;

        vx = 0;
        vy = 0;

        texture.loadFromImage(*image);
        sprite.setTexture (texture);
        sprite.setOrigin(w / 2, h / 2);
    }

    float getX ()
    {
        return x;
    }

    float getY ()
    {
        return y;
    }

    //REKT = rectangle
    sf::FloatRect getRekt()
    {
		return FloatRect(x, y, w, h);
	}

    virtual void update(float time, std::list<Entity*> *l) = 0;

    void del(std::list<Entity*> *l)
    {
        for (std::list<Entity*>::iterator X = l->begin(); X != l->end(); X++)
            if ((*X)->num == num)
            {
                delete (&X);

                l->erase(X);

                break;
            }
    }
};
