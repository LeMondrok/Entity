#pragma once
#include <SFML/Graphics.hpp>
#include <libs/Entity.h>
#include <libs/Player.h>

class Explosion :
    public Entity
{
public:
    float timer;

    Explosion (Image *image, float X, float Y, int W, int H, int Timer, std::list<Entity*> *l, int damage, std::string Name)
    : Entity(image, X, Y, W, H, Name)
    {
        sprite.setTextureRect(IntRect(4, 19, w, h));

        timer = Timer;

        for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); b++)
            if ((*b)->num != this->num && (*b)->type == unfr && (*b)->getRekt().intersects(this->getRekt()))
                (*b)->health -= damage;
    }

    void update(float time, std::list<Entity*> *l);
};

void Explosion::update(float time, std::list<Entity*> *l)
{
    timer -= time;

    if (timer < 0) this->del(l);

    sprite.setPosition(x + w / 2, y + h / 2);
}

class Rocket :
    public Entity
{
public:
    float ax, ay, sx, sy;

    float range;

    float timer;

    Rocket(Image *image, float X, float Y, int W, int H, std::string Name, float Ax, float Ay, int Range)//, state dir)
    : Entity(image, X, Y, W, H, Name)
    {
        range = Range;

        sx = x;
        sy = y;

        ax = Ax;
        ay = Ay;

        vx = 0;
        vy = 0;

        sprite.setTextureRect(IntRect(0, 0, w, h));
        if (ax < 0) sprite.setScale(-1, 1);
    }

    void update(float time, std::list<Entity*> *l);
    void boom(std::list<Entity*> *l);

private:
    void checkCol(float Vx, float Vy, std::list<Entity*> *l);
};

void Rocket::update(float time, std::list<Entity*> *l)
{
    timer += time;

    for (std::list<Entity*>::iterator b = l->begin(); b != l->end(); b++)
        if ((*b)->num != this->num && (*b)->type == unfr && (*b)->getRekt().intersects(this->getRekt())) this->boom(l);

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

void Rocket::boom(std::list<Entity*> *l)
{
    Explosion *E;

    Image *i;

    i = new Image;
    i->loadFromFile("images/b.gif");

    E = new  Explosion(i, x, y, 40, 30, 1000, l, 5, "Explosion");

    l->push_back(E);

    this->del(l);
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

    virtual void shoot(std::list<Entity*> *l, int dir, float *x, float *y) = 0;
};

class Bazooka :
    public Weapon
{
public:
    bool processing;

    Image i;

    Bazooka (int Ammo)
    : Weapon (Ammo)
    {
        i.loadFromFile("images/rocket.png");

        processing = 0;

        magazine = 1;

        reload = 1;
    }

    void update(float time)
    {
        timer += time;

        if (load == 0 && timer >= 1000) load = 1;
    }

    void shoot(std::list<Entity*> *l, int dir, float *x, float *y)
    {
        if (load && processing == 0)
        {
            processing = 1;

            Rocket *r;

            r = new Rocket (&i, *x, *y, 44, 17, "rocket",  0.001 * dir, 0, 5);

            l->push_back (r);

            load = 0;
            timer = 0;

            processing = 0;
        }
    }
};
