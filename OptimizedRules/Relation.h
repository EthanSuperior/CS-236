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
    Relation project(const std::vector<int>& columnPos);
    Relation select(int pos, const std::string& value);
    Relation select(int pos, int pos2);
    Relation rename(int pos, std::string value);
    Relation join(const Relation& relation2);
    Relation Union(const Relation& relation2);
    std::string toString();

private:
    Scheme joinScheme(const Scheme& scheme2);
    static bool canJoin(Tuple t1, Tuple t2, Scheme s1, Scheme s2);
    static Tuple joinTuples(Tuple t1, Tuple t2, Scheme s1, Scheme s2);
};


#endif //RELATIONAL_DATABASE_RELATION_H
