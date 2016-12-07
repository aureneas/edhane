#ifndef EDHANE_WRAPPER_H
#define EDHANE_WRAPPER_H

template <class T, class P>
class Wrapper {
public:
    virtual void add(T*, P*) = 0;
    virtual void add(T*) = 0;
};

#endif // EDHANE_WRAPPER_H
