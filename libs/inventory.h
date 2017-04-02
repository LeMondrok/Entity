#pragma once
#include <SFML/Graphics.hpp>
#include <libs/Entity.h>
#include <libs/Player.h>

class Rocket :
    public Entity
{
public:
    float ax, ay, sx, sy;

    float range;

    Rocket(Image &image, float X, float Y, int W, int H, std::string Name, float Ax, float Ay, int Range)//, state dir)
    : Entity(image, X, Y, W, H, Name)
    {
        range = Range;

        sx = x;
        sy = y;

        ax = Ax;
        ay = Ay;

        vx = 0;
        vy = 0;
    }

    void update(float time, std::list<Entity*> *l);

private:
    void checkCol(float Vx, float Vy, std::list<Entity*> *l);
};

void Rocket::update(float time, std::list<Entity*> *l)
{
    /*for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); l++)
        if ((*b)->getRekt().intersects(this->getRekt())) std::cout << 2;*/

    //std::cout << x << ' ' << y << '\n';

    //std::cout << 1;

    //for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); l++)
    //    if ((*b)->getRekt().intersects(this->getRekt()) && (*b)->num != this->num) this->del(l);

    x += vx * time;
    checkCol(vx, 0, l);
    y += vy * time;
    checkCol(0, vy, l);

    vx += ax * time;
    vy += ay * time;

    sprite.setPosition(x + w / 2, y + h / 2);

    if (vx >= 1)vx = 1;
    if (vy >= 1)vy = 1;


}

void Rocket::checkCol(float Vx, float Vy, std::list<Entity*> *l)
{
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++)
        {
           if (TileMap[i][j] == '0')
           {
                this->del(l);
           }
       }
}

class Inverntory
{
    std::list <int> x;
};

class Weapon
{
public:
    float timer;

    float reload;

    bool load;

    int ammo, magazine;

    Weapon (int Ammo)
    {
        ammo = Ammo;
    }

    virtual void update(float time) = 0;

    virtual void shoot(std::list<Entity*> *l, int dir, int x, int y) = 0;
};

class Bazooka :
    public Weapon
{
public:
    Bazooka (int Ammo)
    : Weapon (Ammo)
    {
        magazine = 1;

        reload = 1;
    }

    void update(float time)
    {
        timer += time;

        if (load == 0 && timer >= 1000) load = 1;
    }

    void shoot(std::list<Entity*> *l, int dir, int x, int y)
    {
        if (load)
        {
            Image i;

            i.loadFromFile("images/b.gif");

            Rocket *r;

            std::cout << 1;

            r = new Rocket (i, x, y, 40, 30, "rocket",  0.001 * dir, 0, 5);

            l->push_back (r);

            load = 0;
            timer = 0;
        }
    }
};
