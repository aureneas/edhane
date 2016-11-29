#include "../include/param.h"

Parametrized::Parametrized() {
    set_param<std::shared_ptr<Parametrized> >((unsigned int)ParamSpecific::INHERIT, nullptr);
    inherit = nullptr;
}

void Parametrized::add_param(unsigned int key, std::shared_ptr<Param> value) {
    std::pair<unsigned int, std::shared_ptr<Param> > p(key, value);
    params.insert(p);
}

template <>
void Parametrized::set_param<Param*>(unsigned int key, Param* value) {
    std::shared_ptr<Param> ptr(value);
    std::unordered_map<unsigned int, std::shared_ptr<Param> >::iterator it = params.find(key);
    if (it == params.end()) {
        add_param(key, ptr);
    } else {
        if (key == (unsigned int)ParamSpecific::INHERIT) {
            if (TypedParam<std::shared_ptr<Parametrized> >* inh =
                    dynamic_cast<TypedParam<std::shared_ptr<Parametrized> >*>(value)) {
                inherit = (inh->data).get();
            } else {
                throw std::string("Inherit must be of parametrized type.");
            }
        }
        it->second = ptr;
    }
}

template <>
Param* Parametrized::get_param<Param*>(unsigned int key) {
    std::unordered_map<unsigned int, std::shared_ptr<Param> >::iterator it = params.find(key);
    if (it == params.end()) {
        if (inherit != nullptr) {
            return inherit->get_param<Param*>(key);
        } else {
            throw std::string("Attempted to access undefined parameter.");
        }
    } else {
        return (it->second).get();
    }
}

bool Parametrized::check_param(unsigned int key) {
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


Article::Article(Parametrized* p) {
    set_param((unsigned int)ParamSpecific::INHERIT, std::shared_ptr<Parametrized>(p));
}

template <>
Param* Article::get_param_chain<Param*>(std::vector<unsigned int>* keys) {
    Param* cur = nullptr;
    for (std::vector<unsigned int>::iterator it = keys->begin(); it < keys->end(); ++it) {
        if (it == keys->begin()) {
            cur = get_param<Param*>(*it);
        } else if (TypedParam<std::shared_ptr<Parametrized> >* typed = static_cast<TypedParam<std::shared_ptr<Parametrized> >*>(cur)) {
            cur = typed->data->get_param<Param*>(*it);
        } else {
            throw std::string("Attempted to access member which does not exist.");
        }
    }
    return cur;
}
