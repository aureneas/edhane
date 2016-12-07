#include "../include/script.h"

Article* Script::key_chain(Article* a, unsigned int first, unsigned int num) {
    Article* b = a;
    for (unsigned int i = first; i < first+num; i++) {
        b = b->get_param<std::shared_ptr<Article> >(act.at(i)).get();
    }
    return b;
}

std::shared_ptr<Param> Script::execute(unsigned int start) {
    unsigned int index = start;
    while (index < act.size()) {
        switch (static_cast<ScriptCommand>(act.at(index))) {

            case ScriptCommand::END:
                return nullptr;
            case ScriptCommand::RETURN:
                return execute(index+1);

            case ScriptCommand::ASSIGNMENT:
                {
                    unsigned int num = act.at(index+1);
                    key_chain(this, index+2, num)->set_param(act.at(index+2+num), execute(index+3+num));
                    break;
                }

            case ScriptCommand::AND:
            case ScriptCommand::OR:
                {
                    std::shared_ptr<Param> p1 = execute(act.at(index+1));
                    std::shared_ptr<Param> p2 = execute(act.at(index+2));
                    if (TypedParam<bool>* b1 = dynamic_cast<TypedParam<bool>*>(p1.get())) {
                        if (TypedParam<bool>* b2 = dynamic_cast<TypedParam<bool>*>(p2.get())) {
                            std::shared_ptr<Param> r(new TypedParam<bool>((act.at(index) == (unsigned int)ScriptCommand::AND) ? (b1->data && b2->data) : (b1->data || b2->data)));
                            return r;
                        }
                    }
                    throw std::string("Params to operator ").append((act.at(index) == (unsigned int)ScriptCommand::AND) ? "&&" : "||").append(" not both boolean values.");
                }

            default:
                throw std::string("Unrecognized command in script.");
        }
    }
}

std::shared_ptr<Param> Script::execute(Article* a, Article* passed) {
    set_inherit(a);
    assimilate(passed);

    std::shared_ptr<Param> rparam(nullptr);
    try {
        rparam = execute(0);
    } catch (std::string err) {
        // popup
    }

    clear_params();
    return rparam;
}
