#ifndef EDHANE_LORD_H
#define EDHANE_LORD_H

template <class T, class P>
class Lord {
public:
    virtual bool add(T) = 0;
    virtual bool add(T, P) = 0;
    virtual T discard(T) = 0;
    virtual T get(P) = 0;
};

#endif // EDHANE_LORD_H
