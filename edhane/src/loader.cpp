#include <functional>
#include "../include/loader.h"


unsigned int StrFileConversion::add_key(std::string s) {
    std::hash<std::string> hash_fn;
    unsigned int h = hash_fn(s) % UINT_MAX;
    while (used_keys.find(h) != used_keys.end()) { h = (h+1) % UINT_MAX; }
    assigned.insert( {{ s, h }} );
    used_keys.insert(h);
    return h;
}

unsigned int StrFileConversion::get_key(std::string s) {
    std::unordered_map<std::string, unsigned int>::iterator it = assigned.find(s);
    if (it != assigned.end()) {
        return it->second;
    } else {
        return add_key(s);
    }
}

bool StrFileConversion::get_line(ALLEGRO_FILE* file) {
    line.clear();
    char* buf;
    bool tag = false;
    unsigned short int open_brackets = 0;
    bool comment = false;

    while (al_fread(file, buf, sizeof(buf)) == sizeof(buf)) {
        if (!line.empty() || !std::regex_match(buf, whitespace)) {
            if (line.empty() && *buf == '[') { tag = true; }
            if (*buf == '[') { open_brackets++; }
            if (*buf == ']') { open_brackets--; }
            line.append(buf);
            if (!comment && regex_match(line, comment_start)){ comment = true; }
            if (comment && regex_match(line, comment_end)) {
                return get_line(file);
            }
            if ((tag && open_brackets == 0) || (!tag && (*buf == '\n' || *buf == ';'))) {
                return true;
            }
        }
    }
    return false;
}


Article* StrFileConversion::load_tag(ALLEGRO_FILE* file, Article* a, std::string str) {
    scope.emplace_front();

    std::smatch s;
    while (get_line(file)) {
        if (regex_match(line, s, tag_close)) {
            if (s.str(2).empty() || s.str(2).compare(str) == 0) {
                return a;
            } else {
                throw std::string("Unexpected closing tag: ").append(line);
            }
        } else if (regex_match(line, s, tag_open)) {
            // do stuff
        } else {
            if (regex_match(line, s, assignment)) {
                // evaluate_param(a, s.str(1), s.str(3));
            }
        }
    }

    scope.pop_front();
    return a;
}

void StrFileConversion::load_file(ALLEGRO_FILE* file) {
    load_tag(file, state, std::string(""));
}
