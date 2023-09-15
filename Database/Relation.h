#ifndef RELATIONAL_DATABASE_RELATION_H
#define RELATIONAL_DATABASE_RELATION_H


#include <string>
#include <set>
#include <utility>
#include "Scheme.h"
#include "Tuple.h"

class Relation {
public:
    Relation(){name="";scheme=Scheme();tuples=std::set<Tuple>{};}
    Relation(std::string rName, Scheme rScheme, std::set<Tuple> rTuples = std::set<Tuple>{}){
        name = std::move(rName);
        scheme = std::move(rScheme);
        tuples = std::move(rTuples);
    }
    std::string name;
    Scheme scheme;
    std::set<Tuple> tuples;
    Relation project(const std::set<int>& columnPos);
    Relation select(int pos, const std::string& value);
    Relation select(int pos, int pos2);
    Relation rename(int pos, std::string value);
    std::string toString();
};


#endif //RELATIONAL_DATABASE_RELATION_H
