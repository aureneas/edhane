#ifndef EDHANE_PARAM_H
#define EDHANE_PARAM_H

#include <memory>
#include <vector>
#include <unordered_map>


struct Param {
    virtual ~Param() {}
};

template <typename T>
struct TypedParam: public Param {
    T data;
    TypedParam(T t) { data = t; }
};


class Article {
private:
    Article* inherit;
    std::unordered_map<unsigned int, std::shared_ptr<Param> > params;
public:
    Article();
    Article(Article*);
    void set_inherit(Article*);

    void add_param(unsigned int, std::shared_ptr<Param>);
    template <typename T> void set_param(unsigned int, T);
    template <typename T> unsigned int get_key(T);
    template <typename T> T get_param(unsigned int);
    bool check_param(unsigned int);

    void clear_params() { params.clear(); }
    void remove_param(unsigned int);

    void assimilate(Article*);
};


template <typename T>
void Article::set_param(unsigned int key, T value) {
    set_param<std::shared_ptr<Param> >(key, std::shared_ptr<Param>(new TypedParam<T>(value)));
}
template <> void Article::set_param<std::shared_ptr<Param> >(unsigned int, std::shared_ptr<Param>);

template <typename T>
unsigned int Article::get_key(T value) {
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
T Article::get_param(unsigned int key) {
    Param* p = get_param<std::shared_ptr<Param> >(key).get();
    if (TypedParam<T>* typed = dynamic_cast<TypedParam<T>*>(p)) {
        return typed->data;
    } else if (p == nullptr) {
        return nullptr;
    } else {
        throw std::string("Member could not be casted to requested type.");
    }
}
template <> std::shared_ptr<Param> Article::get_param<std::shared_ptr<Param> >(unsigned int);

#endif // EDHANE_PARAM_H
