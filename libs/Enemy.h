#pragma once
#include <libs/Entity.h>

class Enemy :
    public Entity
{
    public:
    enum { stay, up, right, down, left, jump} state;
    float timer;

    Enemy(Image &image, float X, float Y, int W, int H, std::string Name)
    : Entity(image, X, Y, W, H, Name)
    {
        state = stay;
        timer = 0;
    }

    void update(float time, std::list<Entity*> *l);

private:
    void checkCol(float Vx, float Vy);

    void AI (float *timer);
};

void Enemy::checkCol(float Vx, float Vy)
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

void Enemy::update (float time, std::list<Entity*> *l)
{
    timer += time;

    AI(&timer);

    switch (state)
    {
        case right : vx =  speed; sprite.setScale( 1, 1); break;
        case left  : vx = -speed; sprite.setScale(-1, 1); break;
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
}

void Enemy::AI (float *timer)
{
    if (*timer > 1000)
    {
        //std::cout << 999999999 << ' ';
        *timer = 0;
    }

    if (*timer > 500)
    {
        state = left;
        speed = 0.1;
    }
    else
    {
        state = right;
        speed = 0.1;
    }
}
