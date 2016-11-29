#ifndef OPTIONS_H
#define OPTIONS_H

#include "param.h"

class Options: public Parametrized {
protected:
    // global options
    static unsigned short int FRAME_RATE;

public:
    int get_frame_rate();
};

#endif // OPTIONS_H
