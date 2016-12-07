#include "../include/param.h"

Article::Article() {
    inherit = nullptr;
}

Article::Article(Article* a) {
    inherit = a;
}

void Article::set_inherit(Article* a) {
    inherit = a;
}

void Article::add_param(unsigned int key, std::shared_ptr<Param> value) {
    std::pair<unsigned int, std::shared_ptr<Param> > p(key, value);
    params.insert(p);
}

template <>
void Article::set_param<std::shared_ptr<Param> >(unsigned int key, std::shared_ptr<Param> value) {
    std::unordered_map<unsigned int, std::shared_ptr<Param> >::iterator it = params.find(key);
    if (it == params.end()) {
        add_param(key, value);
    } else {
        it->second = value;
    }
}

template <>
std::shared_ptr<Param> Article::get_param<std::shared_ptr<Param> >(unsigned int key) {
    std::unordered_map<unsigned int, std::shared_ptr<Param> >::iterator it = params.find(key);
    if (it == params.end()) {
        if (inherit != nullptr) {
            return inherit->get_param<std::shared_ptr<Param> >(key);
        } else {
            throw std::string("Attempted to access undefined parameter.");
        }
    } else {
        return it->second;
    }
}

bool Article::check_param(unsigned int key) {
    if (params.find(key) != params.end()) {
        return true;
    } else {
        if (inherit != nullptr) {
            return inherit->check_param(key);
        } else {
            return false;
        }
    }
}

void Article::remove_param(unsigned int key) {
    std::unordered_map<unsigned int, std::shared_ptr<Param> >::iterator it = params.find(key);
    if (it != params.end()) { params.erase(it); }
}

void Article::assimilate(Article* a) {
    for (std::unordered_map<unsigned int, std::shared_ptr<Param> >::iterator it = a->params.begin(); it != a->params.end(); ++it) {
        set_param(it->first, it->second.get());
    }
}
