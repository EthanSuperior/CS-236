#ifndef PARSER_DATALOGPROGRAM_H
#define PARSER_DATALOGPROGRAM_H

#include <string>
#include <sstream>
#include <vector>
#include <set>

#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
public:
    std::vector<Predicate> Schemes;
    std::vector<Predicate> Facts;
    std::vector<Rule> Rules;
    std::vector<Predicate> Queries;
    std::set<std::string> Domain;

    std::string toString() {
        std::stringstream out;
        out << "Schemes(" << Schemes.size() << "):" << std::endl;
        if (!Schemes.empty()) {
            for (Predicate p:Schemes)
                out << "  " << p.toString() << std::endl;
        }
        out << "Facts(" << Facts.size() << "):" << std::endl;
        if (!Facts.empty()) {
            for (Predicate p:Facts)
                out << "  " << p.toString() << "." << std::endl;
        }
        out << "Rules(" << Rules.size() << "):" << std::endl;
        if (!Rules.empty()) {
            for (Rule rule:Rules)
                out << "  " << rule.toString() << "." << std::endl;
        }
        out << "Queries(" << Queries.size() << "):" << std::endl;
        if (!Queries.empty()) {
            for (Predicate p:Queries)
                out << "  " << p.toString() << "?" << std::endl;
        }
        out << "Domain(" << Domain.size() << "):" << std::endl;
        if (!Domain.empty()) {
            for (const std::string &name:Domain)
                out << "  " << name << std::endl;
        }
        return out.str();
    }

    DatalogProgram()= default;
};

#endif //PARSER_DATALOGPROGRAM_H
