#include "../include/wrapper.h"

Wrapper::Wrapper(unsigned int ic) {
    capacity = ic;
    vassals = new shared_ptr<Form>[capacity];
    first = capacity/2;
    last = first+1;
}

template <>
void Wrapper::add<Point>(Form* f, Point* p) {

}

void Wrapper::add(Form* f) {
    add(f, f->get_pos());
}
