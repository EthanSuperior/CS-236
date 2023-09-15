#ifndef PARSER_RULE_H
#define PARSER_RULE_H

#include <string>
#include <sstream>
#include <utility>
#include <vector>

#include "Predicate.h"

class Rule {
public:
    Predicate headPred = Predicate("");
    std::vector<Predicate> body;

    std::string toString() const {
        std::stringstream out;
        if (!body.empty()) {
            out << headPred.toString() << " :- " << body.at(0).toString();
            for (unsigned int i = 1; i < body.size(); i++)
                out << "," << body.at(i).toString();
        }
        return out.str();
    }

    Rule(){
        headPred = Predicate();
    };
    explicit Rule(Predicate head) {
        headPred = std::move(head);
    };
};

#endif //PARSER_RULE_H
