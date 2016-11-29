#include <allegro5/allegro.h>
#include "../include/options.h"

unsigned short int Options::FRAME_RATE;

int Options::get_frame_rate() {
    return Options::FRAME_RATE;
}
