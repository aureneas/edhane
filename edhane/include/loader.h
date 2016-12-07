#ifndef EDHANE_LOADER_H
#define EDHANE_LOADER_H

#include <forward_list>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <regex>
#include "state.h"

class StrFileConversion {
private:
    State* state;

    std::unordered_map<std::string, unsigned int> assigned;
    std::forward_list<std::unordered_set<unsigned int> > scope; // mapping from strings to the parameter keys
    std::unordered_set<unsigned int> used_keys;
    unsigned int add_key(std::string);

    std::regex whitespace;
    std::regex comment_start;
    std::regex comment_end;

    std::regex tag_open;
    std::regex tag_close;
    std::regex param_id;
    std::regex param_extends;

    std::regex assignment;
    //void evaluate_param(Article*, std::string, std::string);

    std::regex declare_str;

    std::string line;

public:
    StrFileConversion() : whitespace("\s+"),
                comment_start("\[!\-\-"),
                comment_end("\-\-\]"),
                tag_open("\[\s*(\w[\w\d_]*)\s*(.*)\]"),
                tag_close("\[\s*(/\s*(\w[\w\d_)|end)\s*\]"),
                param_id("\bid\s*:\s*(([\w_][\w\d_]*)(\((.*)\))?)"),
                param_extends("\bextends\s*:\s*([\w_][\w\d_\.]*)"),
                assignment("([\w_][\w\d_]*)\s*(=\s*(.*)\s*)?"),
                declare_str("\"(.*)\"") {}

    unsigned int get_key(std::string);

    bool get_line(ALLEGRO_FILE*);
    std::string current_line() { return line; }

    Article* load_tag(ALLEGRO_FILE*, Article*, std::string);
    void load_file(ALLEGRO_FILE*);

};

#endif // EDHANE_LOADER_H
