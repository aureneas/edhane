#include "../include/input.h"

const unsigned int MOUSE_LEFT_DOUBLE = 3;

void InputManager::set_input(unsigned int key, bool value) {
    std::unordered_map<unsigned int, bool>::iterator it = cinpts.find(key);
    if (it != cinpts.end()) {
        it->second = value;
    } else {
        cinpts.insert({ {key, value} });
    }
}

bool InputManager::get_input(unsigned int key) {
    std::unordered_map<unsigned int, bool>::iterator it = cinpts.find(key);
    return ((it != cinpts.end()) ? it->second : false);
}

InputReceived InputManager::update_frame() {
    tsprs[MOUSE_LEFT_BUTTON-1]++;
    tsprs[MOUSE_RIGHT_BUTTON-1]++;
    if (clrel[MOUSE_LEFT_DOUBLE-1] && crdl[0] == crdmouse[0] && crdl[1] == crdmouse[1]) {
        clrel[MOUSE_LEFT_DOUBLE-1] = false;
        clrel[MOUSE_LEFT_BUTTON-1] = false;
        return ((options->get_frame_rate() >= 2*tsprs[MOUSE_LEFT_BUTTON-1]) ?
            InputReceived::MOUSE_DOUBLE_CLICK : InputReceived::MOUSE_LEFT_CLICK);
    } else if (clrel[MOUSE_LEFT_BUTTON-1] && crdl[0] == crdmouse[0] && crdl[1] == crdmouse[1]
            && options->get_frame_rate() < 2*tsprs[MOUSE_LEFT_BUTTON-1]) {
        clrel[MOUSE_LEFT_BUTTON-1] = false;
        return InputReceived::MOUSE_LEFT_CLICK;
    } else if (clrel[MOUSE_RIGHT_BUTTON-1] && crdr[0] == crdmouse[0] && crdr[1] == crdmouse[1]
            && options->get_frame_rate() < 2*tsprs[MOUSE_RIGHT_BUTTON-1]) {
        clrel[MOUSE_RIGHT_BUTTON-1] = false;
        return InputReceived::MOUSE_RIGHT_CLICK;
    }
    return InputReceived::OTHER;
}

InputReceived InputManager::update_event(ALLEGRO_EVENT* e) {
    // do stuff
    switch (e->type) {
        case ALLEGRO_EVENT_MOUSE_AXES:
            {
                crdmouse[0] = e->mouse.x;
                crdmouse[1] = e->mouse.y;
                if (!frozen && get_input(MOUSE_LEFT_BUTTON-1)) {
                    return InputReceived::MOUSE_DRAG;
                }
                break;
            }
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            {
                crdmouse[0] = e->mouse.x;
                crdmouse[1] = e->mouse.y;
                if (!frozen) {
                    if (e->mouse.button == MOUSE_LEFT_BUTTON) {
                        if (crdl[0] != e->mouse.x || crdl[1] != e->mouse.y
                                || options->get_frame_rate() < 2*tsprs[MOUSE_RIGHT_BUTTON-1]) {
                            tsprs[MOUSE_LEFT_BUTTON-1] = 0;
                        }
                        set_input(MOUSE_LEFT_BUTTON-1, true);
                        crdl[0] = e->mouse.x;
                        crdl[1] = e->mouse.y;
                    } else {
                        tsprs[MOUSE_RIGHT_BUTTON-1] = 0;
                        set_input(MOUSE_RIGHT_BUTTON-1, true);
                        crdr[0] = e->mouse.x;
                        crdr[1] = e->mouse.y;
                    }
                }
                break;
            }
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            {
                crdmouse[0] = e->mouse.x;
                crdmouse[1] = e->mouse.y;
                if (e->mouse.button == MOUSE_LEFT_BUTTON) {
                    set_input(MOUSE_LEFT_BUTTON-1, false);
                    if (!frozen) {
                        if (crdl[0] == e->mouse.x && crdl[1] == e->mouse.y
                                && options->get_frame_rate() >= 2*tsprs[MOUSE_RIGHT_BUTTON-1]) {
                            if (clrel[MOUSE_LEFT_BUTTON-1]) {
                                clrel[MOUSE_LEFT_DOUBLE-1] = true;
                            } else {
                                clrel[MOUSE_LEFT_BUTTON-1] = true;
                            }
                        } else if (crdl[0] != e->mouse.x || crdl[1] != e->mouse.y) {
                            return InputReceived::MOUSE_DRAG_RELEASE;
                        }
                    }
                } else {
                    set_input(MOUSE_RIGHT_BUTTON-1, false);
                    if (!frozen) {
                        if (crdr[0] == e->mouse.x && crdr[1] == e->mouse.y
                                && options->get_frame_rate() >= 2*tsprs[MOUSE_RIGHT_BUTTON-1]) {
                            clrel[MOUSE_RIGHT_BUTTON-1] = true;
                            return InputReceived::MOUSE_RIGHT_CLICK;
                        }
                    }
                }
                break;
            }
        case ALLEGRO_EVENT_KEY_DOWN:
            {
                unsigned int key = options->get_key(e->keyboard.keycode);
                if (key > 0) {
                    set_input(key, true);
                    return InputReceived::KEY_PRESSED;
                }
                break;
            }
        case ALLEGRO_EVENT_KEY_UP:
            {
                unsigned int key = options->get_key(e->keyboard.keycode);
                if (key > 0) {
                    set_input(key, false);
                    return InputReceived::KEY_RELEASED;
                }
                break;
            }
    }
    return InputReceived::OTHER;
}
