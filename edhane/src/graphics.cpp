#include "../include/graphics.h"

ALLEGRO_COLOR color_blend(ALLEGRO_COLOR* c1, ALLEGRO_COLOR* c2, float bias) {
    if (bias == 1) { return *c1; } else if (bias == 0) { return *c2; }
    float r1, r2, g1, g2, b1, b2, a1, a2;
    if (c1 != nullptr) { al_unmap_rgba_f(*c1, &r1, &g1, &b1, &a1); }
    if (c2 != nullptr) { al_unmap_rgba_f(*c2, &r2, &g2, &b2, &a2); }
    return al_map_rgba_f((bias*(r1-r2))+r2, (bias*(g1-g2))+g2, (bias*(b1-b2))+b2, (bias*(a1-a2))+a2);
}

ALLEGRO_COLOR color_overlay(ALLEGRO_COLOR* c1, ALLEGRO_COLOR* c2) {
    if (c1 == nullptr) { return *c2; } else if (c2 == nullptr) { return *c1; }
    float r1, r2, g1, g2, b1, b2, a1, a2;
    al_unmap_rgba_f(*c1, &r1, &g1, &b1, &a1);
    al_unmap_rgba_f(*c2, &r2, &g2, &b2, &a2);
    return al_map_rgba_f(r1*r2, g1*g2, b1*b2, a1*a2);
}


Graphics::Graphics() {
    tint = nullptr;
    res = 1.0;
}

void Graphics::set_tint(float r, float g, float b, float a) {
    ALLEGRO_COLOR c = al_map_rgba_f(r, g, b, a);
    tint = &c;
}

void Graphics::shift_tint(float dr, float dg, float db, float da) {
    float r, g, b, a;
    al_unmap_rgba_f(*tint, &r, &g, &b, &a);
    ALLEGRO_COLOR c = al_map_rgba_f(r+dr, g+dg, b+db, a+da);
    tint = &c;
}

void Graphics::draw(ALLEGRO_BITMAP* bmp, float x, float y,
                    ALLEGRO_COLOR* blend, float bias,
                    ALLEGRO_COLOR* overlay, bool tint_override,
                    float xres, float yres, bool res_override, int flags) {
    if (bmp != nullptr) {
        if (bias != 1 && !tint_override) {
            if (tint != nullptr) {
                ALLEGRO_COLOR nblend = color_blend(blend, tint, bias);
                draw(bmp, x, y, &nblend, 1, overlay, tint_override, xres, yres, res_override, flags);
            } else {
                draw(bmp, x, y, blend, 1, overlay, tint_override, xres, yres, res_override, flags);
            }
        } else if (!tint_override) {
            if (blend != nullptr) {
                if (overlay != nullptr) {
                    ALLEGRO_COLOR noverlay = color_overlay(overlay, blend);
                    draw(bmp, x, y, blend, bias, &noverlay, true, xres, yres, res_override, flags);
                } else {
                    draw(bmp, x, y, blend, bias, blend, true, xres, yres, res_override, flags);
                }
            } else {
                draw(bmp, x, y, blend, bias, overlay, true, xres, yres, res_override, flags);
            }
        } else if (!res_override && res != 1) {
            draw(bmp, x, y, blend, bias, overlay, tint_override, xres*res, yres*res, true, flags);
        } else {
            if (xres != 1 || yres != 1) {
                int w = al_get_bitmap_width(bmp);
                int h = al_get_bitmap_height(bmp);
                if (overlay != nullptr) {
                    al_draw_tinted_scaled_bitmap(bmp, *overlay, 0, 0, w, h, x, y, w*xres, h*yres, flags);
                } else {
                    al_draw_scaled_bitmap(bmp, 0, 0, w, h, x, y, w*xres, h*yres, flags);
                }
            } else if (overlay != nullptr) {
                al_draw_tinted_bitmap(bmp, *overlay, x, y, flags);
            } else {
                al_draw_bitmap(bmp, x, y, flags);
            }
        }
    }
}
