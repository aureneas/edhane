#ifndef EDHANE_GRAPHICS_H
#define EDHANE_GRAPHICS_H

#include <allegro5/allegro.h>

class Graphics {
private:
    ALLEGRO_COLOR* tint;
    float res;

public:
    Graphics();

    void set_tint(float, float, float, float = 1);
    void shift_tint(float, float, float, float = 0);

    void draw(ALLEGRO_BITMAP*, float, float,
              ALLEGRO_COLOR* = nullptr, float = 0,
              ALLEGRO_COLOR* = nullptr, bool = false,
              float = 1, float = 1, bool = false, int = 0);
};

#endif // EDHANE_GRAPHICS_H
