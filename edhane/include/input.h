#ifndef INPUT_H
#define INPUT_H

#include <memory>
#include <unordered_map>
#include <allegro5/allegro.h>
#include "options.h"

enum class InputReceived {
    MOUSE_DRAG,             // the mouse has clicked and is now dragging
    MOUSE_DRAG_RELEASE,     // the mouse was dragging and has released the mouse button
    MOUSE_LEFT_CLICK,       // the mouse left clicked
    MOUSE_RIGHT_CLICK,      // the mouse right clicked
    MOUSE_DOUBLE_CLICK,     // the mouse double clicked
    KEY_PRESSED,            // a (relevant) key was pressed
    KEY_RELEASED,           // a (relevant) key was released
    OTHER                   // some other input was received, but has no case to handle it
};

const unsigned int MOUSE_LEFT_BUTTON = 1;
const unsigned int MOUSE_RIGHT_BUTTON = 2;

/**
 *  Basic input controller
 */
class InputManager {
protected:
    Options* options;

    bool frozen;            // whether or not inputs are currently frozen

    std::unordered_map<unsigned int, bool> cinpts;  // which inputs are being held
    int crdmouse[2];           // the current coordinates of the mouse
    int crdl[2];               // the coordinates of the last left click
    int crdr[2];               // the coordinates of the last right click
    unsigned short int tsprs[2];        // the number of frames since the last mouse button press
    bool clrel[3];                      // whether the click has been released recently

    void set_input(unsigned int, bool);

public:
    InputReceived update_frame();
    InputReceived update_event(ALLEGRO_EVENT*);

    void set_frozen(bool b) { frozen = b; }
    void set_options(Options* o) { options = o; }

    bool get_input(unsigned int);

};

#endif // INPUT_H
