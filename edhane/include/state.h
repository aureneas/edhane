#ifndef STATE_H
#define STATE_H

#include <allegro5/allegro.h>
#include "run.h"
#include "input.h"
#include "display.h"

/**
 *  Superclass for states of the game: the main menu, the load game screen, the new game screens, the actual game
 */
class State {
protected:
    ALLEGRO_BITMAP* bg;

    InputManager input;
    DisplayManager* control;

public:
    State(DisplayManager*);
    virtual ~State();

    RunResult run(ALLEGRO_EVENT*);
    virtual RunResult update_frame();
    virtual RunResult update_event(ALLEGRO_EVENT*);

};

#endif // STATE_H
