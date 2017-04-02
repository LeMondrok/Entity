#pragma once
#include <libs/Entity.h>
#include <libs/inventory.h>
#include <malloc.h>

class Player :
    public Entity
{
public:
    enum { stay, up, right, down, left, jump} state;
    bool spawn;

    std::list <Weapon*> weapons;

    Player(Image &image, float X, float Y, int W, int H, std::string Name)
    : Entity(image, X, Y, W, H, Name)
    {
        state = stay;

        spawn = 1;

        Bazooka *b;

        b = new Bazooka (8);

        weapons.push_back (b);
    }

    void update(float time, std::list<Entity*> *l);

private:
    void checkCol(float Vx, float Vy);

    void control (std::list<Entity*> *l);
};

void Player::checkCol(float Vx, float Vy)
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

void Player::update(float time, std::list<Entity*> *l)
{
    control(l);

    switch (state)
    {
        case right : vx =  speed; break;
        case left  : vx = -speed; break;
        case up    :              break;
        case down  : vx = 0;      break;
        case stay  :              break;
    }

    for (std::list<Weapon*>::iterator g = weapons.begin(); g != weapons.end(); g++)
        (*g)->update(time);

    /*for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); b++)
        if ((*b)->getRekt().intersects(this->getRekt())) std::cout << 1;*/

    x += vx * time;
    checkCol(vx, 0);

    y += vy * time;
    checkCol(0, vy);

    vy +=  0.0015 * time;

    sprite.setPosition(x + w / 2, y + h / 2);

    setPlayerCoordinateForView(x, y);
}

void Player::control(std::list<Entity*> *l)
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
        if (sf::Keyboard::isKeyPressed(Keyboard::Space))// && spawn == 1)
        {
            if (vx > 0)
                weapons.back()->shoot(l,  1, x, y);
            else
                weapons.back()->shoot(l, -1, x, y);
        }
    }
}
