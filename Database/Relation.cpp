#include <iostream>
#include <sstream>
#include "Relation.h"

using namespace std;

Relation Relation::project(const set<int>& columnPos) {
    Scheme modScheme;
    set<Tuple> modTuples;
    if(columnPos.empty())
        return Relation(name,modScheme,modTuples);
    for(int index : columnPos)
        modScheme.push_back(scheme[index]);
    for(Tuple t:tuples) {
        Tuple temp;
        for(int index : columnPos)
            temp.push_back(t[index]);
        modTuples.emplace(temp);
    }
    return Relation(name,modScheme,modTuples);
}
Relation Relation::select(int pos, int pos2) {
    set<Tuple> modTuples;
    for(Tuple t:tuples) {
        if(t[pos] == t[pos2])
            modTuples.emplace(t);
    }
    return Relation(name,scheme,modTuples);
}
Relation Relation::select(int pos, const string& value) {
    set<Tuple> modTuples;
    for(Tuple t:tuples) {
        if(t[pos] == value)
            modTuples.emplace(t);
    }
    return Relation(name,scheme,modTuples);
}

Relation Relation::rename(int pos, string value) {
    Scheme modScheme = scheme;
    modScheme[pos] = value;
    return Relation(name,modScheme,tuples);
}

std::string Relation::toString() {
    stringstream out;
    for (Tuple t:tuples) {
        out << "  " << scheme[0] << "=" << t[0];
        for (int i = 1; i < (int) scheme.size(); i++)
            out << ", " << scheme[i] << "=" << t[i];
        out << endl;
    }
    return out.str();
}
