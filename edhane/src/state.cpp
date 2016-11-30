#include "../include/state.h"

RunResult State::run(ALLEGRO_EVENT* e) {
    if (e->type == ALLEGRO_EVENT_TIMER) {
        return update_frame();
    } else {
        return update_event(e);
    }
}

RunResult State::update_frame() {
    InputReceived ir = input.update_frame();
    RunResult rr;
    for (std::vector<std::shared_ptr<Module> >::iterator it = modules.begin(); it < modules.end(); ++it) {
        rr = (*it)->update_event(ir);
        (*it)->update_frame();
    }
    return rr;
}

RunResult State::update_event(ALLEGRO_EVENT* e) {
    InputReceived ir = input.update_event(e);
    RunResult rr;
    for (std::vector<std::shared_ptr<Module> >::iterator it = modules.begin(); it < modules.end(); ++it) {
        rr = (*it)->update_event(ir);
    }
    return rr;
}
