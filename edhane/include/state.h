#ifndef EDHANE_STATE_H
#define EDHANE_STATE_H

#include <allegro5/allegro.h>
#include <vector>
#include "run.h"
#include "input.h"
#include "module.h"

/**
 *  Superclass for states of the game: the main menu, the load game screen, the new game screens, the actual game
 */
class State: public Article {
protected:
    InputManager input;
    std::vector<std::shared_ptr<Module> > modules;

public:
    // template <> void set_param<std::shared_ptr<Module> >(unsigned int, std::shared_ptr<Module>);

    RunResult run(ALLEGRO_EVENT*);
    virtual RunResult update_frame();
    virtual RunResult update_event(ALLEGRO_EVENT*);

};

#endif // EDHANE_STATE_H
