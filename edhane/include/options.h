#ifndef EDHANE_OPTIONS_H
#define EDHANE_OPTIONS_H

#include "param.h"

class Options: public Parametrized {
protected:
    // global options
    static unsigned short int FRAME_RATE;

public:
    int get_frame_rate();
};

#endif // EDHANE_OPTIONS_H
