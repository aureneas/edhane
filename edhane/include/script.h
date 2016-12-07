#ifndef EDHANE_SCRIPT_H
#define EDHANE_SCRIPT_H

#include <vector>
#include "param.h"

enum class ScriptCommand : unsigned int {
    END = 0,
    RETURN = 1,

    ASSIGNMENT = 2,

    AND = 3,
    OR = 4,
    NOT = 5
};

class Script: public Article {
private:
    Article values;
    std::vector<unsigned int> act;

    Article* key_chain(Article*, unsigned int, unsigned int);

    std::shared_ptr<Param> execute(unsigned int);
public:
    std::shared_ptr<Param> execute(Article*, Article*);
};

#endif // EDHANE_SCRIPT_H
