#include "../include/state.h"

// TODO remove test cout functions, then this include and namespace
#include <iostream>


State::State(DisplayManager* dsp) {
    control = dsp;
}

State::~State() {
    delete control;
}

RunResult State::run(ALLEGRO_EVENT* e) {
    if (e->type == ALLEGRO_EVENT_TIMER) {
        return update_frame();
    } else {
        return update_event(e);
    }
}

RunResult State::update_frame() {
    input.update_frame();
    return RunResult::CONTINUE;
}

RunResult State::update_event(ALLEGRO_EVENT* e) {
    switch (input.update_event(e)) {
        case InputReceived::OTHER:
            std::cout << "No event.\n";
            break;
        case InputReceived::KEY_PRESSED:
            std::cout << "Key pressed.\n";
            break;
        case InputReceived::KEY_RELEASED:
            std::cout << "Key released.\n";
            break;
        case InputReceived::MOUSE_DRAG:
            std::cout << "Mouse drag.\n";
            break;
        case InputReceived::MOUSE_DRAG_RELEASE:
            std::cout << "Mouse drag released.\n";
            break;
        case InputReceived::MOUSE_LEFT_CLICK:
            std::cout << "Mouse left click.\n";
            break;
        case InputReceived::MOUSE_RIGHT_CLICK:
            std::cout << "Mouse right click.\n";
            break;
        case InputReceived::MOUSE_DOUBLE_CLICK:
            std::cout << "Mouse double click.\n";
            break;
    }
    return control->update_event(e);
}
