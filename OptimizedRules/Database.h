#ifndef RELATIONAL_DATABASE_DATABASE_H
#define RELATIONAL_DATABASE_DATABASE_H

#include <map>
#include <sstream>
#include "Relation.h"

class Database : public std::map<std::string,Relation>{
public:
    std::string toString() {
        std::stringstream out;
        for (auto &i : *this) {
            out << i.second.name << ":\n" << i.second.toString();
        }
        return out.str();
    }
};

#endif //RELATIONAL_DATABASE_DATABASE_H
