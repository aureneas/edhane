#ifndef EDHANE_MODULE_H
#define EDHANE_MODULE_H

#include "run.h"
#include "param.h"
#include "input.h"
#include "graphics.h"

class Module: public Parametrized {
private:
    Graphics graphics;

public:
    virtual RunResult update_frame() = 0;
    virtual RunResult update_event(InputReceived) = 0;

};

#endif // EDHANE_MODULE_H
