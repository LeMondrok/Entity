#include <libs/draw.h>
#include <libs/Entity.h>
#include <set>

using namespace sf;

class gameLoop
{
public:
    Sprite s_map;
    Image map_image;
    Texture map;

    gameLoop (RenderWindow *Window, bool choose)
    {
        window = Window;

        map_image.loadFromFile("images/map.png");

        map.loadFromImage(map_image);

        s_map.setTexture(map);
    }

    update()
    {
        drawMap(window, &s_map);
    }

private:
    RenderWindow *window;

    Player *p;

    std::set <Entity> enemies;

};
