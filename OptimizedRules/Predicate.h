#ifndef PARSER_PREDICATE_H
#define PARSER_PREDICATE_H

#include <utility>
#include <string>
#include <sstream>
#include <vector>

#include "Parameter.h"

class Predicate {
public:
    std::string name;
    std::vector<Parameter> prams;

    std::string toString() const {
        std::stringstream out;
        if(!prams.empty()) {
            out << name << "(" << prams.at(0).toString();
            for (unsigned int i = 1; i < prams.size(); i++)
                out << "," << prams.at(i).toString();
            out << ")";
        }
        return out.str();
    }

    Predicate(){
        name="";
    }
    explicit Predicate(std::string n) {
        name = std::move(n);
    };
};

#endif //PARSER_PREDICATE_H
