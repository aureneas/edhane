#ifndef PARAM_H
#define PARAM_H

#include <memory>
#include <vector>
#include <unordered_map>


enum class ParamSpecific: unsigned int {
    THIS = 0,
    INHERIT = 1
};


struct Param {
    virtual ~Param() {}
};

template <typename T>
struct TypedParam: public Param {
    T data;
    TypedParam(T t) { data = t; }
};


class Parametrized {
private:
    Parametrized* inherit;
    std::unordered_map<unsigned int, std::shared_ptr<Param> > params;
public:
    Parametrized();
    virtual void add_param(unsigned int, std::shared_ptr<Param>);
    template <typename T> void set_param(unsigned int, T);
    template <typename T> unsigned int get_key(T);
    template <typename T> T get_param(unsigned int);
    bool check_param(unsigned int);
};

class Article: public Parametrized {
public:
    Article() {}
    Article(Parametrized*);
    template <typename T> T get_param_chain(std::vector<unsigned int>*);
};


template <typename T>
void Parametrized::set_param(unsigned int key, T value) {
    set_param<Param*>(key, new TypedParam<T>(value));
}

template <typename T>
unsigned int Parametrized::get_key(T value) {
    for (std::unordered_map<unsigned int, std::shared_ptr<Param> >::iterator it = params.begin(); it != params.end(); ++it) {
        if (TypedParam<T>* t = dynamic_cast<TypedParam<T>* >((it->second).get())) {
            if (t->data == value) {
                return it->first;
            }
        }
    }
    return 0;
}

template <typename T>
T Parametrized::get_param(unsigned int key) {
    Param* p = get_param<Param*>(key);
    if (TypedParam<T>* typed = dynamic_cast<TypedParam<T>*>(p)) {
        return typed->data;
    } else if (p == nullptr) {
        return nullptr;
    } else {
        throw std::string("Member could not be casted to requested type.");
    }
}


template <typename T>
T Article::get_param_chain(std::vector<unsigned int>* keys) {
    Param* p = get_param_chain<Param*>(keys);
    if (TypedParam<T>* typed = dynamic_cast<TypedParam<T>*>(p)) {
        return typed->data;
    } else {
        throw std::string("Member could not be casted to requested type.");
    }
}

#endif // PARAM_H
