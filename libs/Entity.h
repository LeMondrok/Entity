#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <libs/map.h>
#include <libs/view.h>

class Entity
{
public:
    float vx, vy, x, y, speed;
    int health, w, h;
    bool life, onGround, onLadder, isMove;

    sf::Texture texture;
	sf::Sprite sprite;
	std::string name;

    Entity (sf::Image &image, float X, float Y, int W, int H, std::string Name)
    {
        texture.loadFromImage(image);
        sprite.setTexture (texture);
        sprite.setOrigin(w / 2, h / 2);

        x = X;
        y = Y;
        w = W;
        h = H;

        speed = 0;

        name = Name;
    }

    float getX ()
    {
        return x;
    }

    float getY ()
    {
        return y;
    }

    void checkCol(int Vx, int Vy);

    virtual void update() = 0;
};

void Entity::checkCol(int Vx, int Vy)
{
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++)
        {
           if (TileMap[i][j] == '0')
           {
                if (Vy > 0)
                {
                    y = i * 32 - h;
                    vy = 0;
                    onGround = true;
                }

                if (Vy < 0)
                {
                    y = i * 32 + 32;
                    vy = 0;
                }

                if (Vx > 0)
                {
                    x = j * 32 - w;
                }

                if (Vx < 0)
                {
                    x = j * 32 + 32;
                }
           }
       }
}

class Player : Entity
{
public:
    enum { stay, up, right, down, left, jump} state;

    Player(sf::Image &image, float X, float Y, int W, int H, std::string Name)
    : Entity(image, X, Y, W, H, Name)
    {
        state = stay;
    }

    void update(float time);

private:
    void control ();
};

void Player::update(float time)
{
    control();

    switch (state)
    {
        case right : vx =  speed; break;
        case left  : vx = -speed; break;
        case up    :              break;
        case down  : vx = 0;      break;
        case stay  :              break;
    }

    x += vx * time;
    checkCol(vx, 0);

    y += vy * time;
    checkCol(0, vy);

    vy +=  0.0015 * time;

    sprite.setPosition(x + w / 2, y + h / 2);

    setPlayerCoordinateForView(x, y);
}

void Player::control()
{
        if (sf::Keyboard::isKeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(Keyboard::Left))
            {
                state = left;
                speed = 0.1;
            }
            if (sf::Keyboard::isKeyPressed(Keyboard::Right))
            {
                state = right;
                speed = 0.1;
            }
            if (sf::Keyboard::isKeyPressed(Keyboard::Up) && onGround)
            {
                state = jump;

                onGround = 0;

                vy = -0.6;
            }
            if (sf::Keyboard::isKeyPressed(Keyboard::Down))
            {
                state = down;

                speed = 0;
            }
        }
    }
