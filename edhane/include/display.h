#ifndef DISPLAY_H
#define DISPLAY_H

#include <allegro5/allegro.h>
#include "run.h"

class DisplayManager {
private:

public:
    RunResult update_event(ALLEGRO_EVENT*);
};

#endif // DISPLAY_H
