#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include "Relation.h"

using namespace std;

Relation Relation::project(const vector<int>& columnPos) {
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
    modScheme[pos] = std::move(value);
    return Relation(name,modScheme,tuples);
}

Relation Relation::join(Relation relation2) {
    //std::cout<<"j-r1:"<< toString()<<", "<<std::endl;
    //std::cout<<"j-r2:"<< relation2.toString()<<", ";
    Scheme newScheme = joinScheme(relation2.scheme);
    //std::cout<<"j-nS:"<< newScheme.size()<<", ";
    Relation newResult = Relation("Temp", newScheme);
    //std::cout<<newResult.toString()<<std::endl;
    if(!tuples.empty())
        for(Tuple t:tuples)
            for(Tuple t2:relation2.tuples) {
                //std::cout<<"j-T1s:"<<t.size()<<", T2s:"<<t2.size()<<std::endl;
                //std::cout<<"j-S1s:"<<scheme.size()<<", S2s:"<<relation2.scheme.size()<<std::endl;
                if (canJoin(t, t2, scheme, relation2.scheme)) {
                    //std::cout<<"j-cJ:T";
                    newResult.tuples.emplace(joinTuples(t, t2, scheme, relation2.scheme));
                }
            }
    else{
        newResult.tuples=relation2.tuples;
    }
    return newResult;
}

Scheme Relation::joinScheme(Scheme scheme2) { //schemeLeft -> A,B
											  //schemeRIght -> B,C A,B,C
    Scheme result=scheme;
    //std::cout<<"jS:"<<result.size()<<std::endl;
    for(const string& str:scheme2){
        bool included = false;
        for (int i = 0;i < (int)scheme.size(); i++)
            if (str == scheme.at(i)) {
                included = true;
                break;
            }
        if(!included)
            result.push_back(str);

    }
    //std::cout<<"jS:"<<result.size()<<std::endl;
    return result;
}

bool Relation::canJoin(Tuple t1, Tuple t2, Scheme s1, Scheme s2) {
    for(int i=0; i< (int)s1.size();i++)
        for(int j=0; j< (int)s2.size();j++)
            if(s1.at(i)==s2.at(j) && t1.at(i)!=t2.at(j))
                return false;
    return true;
}

Tuple Relation::joinTuples(Tuple t1, Tuple t2, Scheme s1, Scheme s2) {
    Tuple result = t1;
    //std::cout<<"j-jTF:";
    for (int i = 0;i<(int)s2.size();i++){
        bool included = false;
        for (int j = 0;j<(int)s1.size();j++)
            if (s2.at(i) == s1.at(j)) {
                included = true;
                break;
            }
        if(!included) {
            result.push_back(t2.at(i));
            //std::cout<<t2.at(i)<<", ";
        }
    }
    return result;
}

Relation Relation::Union(Relation relation2) {
    set<Tuple> unionTuples = this->tuples;
    for(const Tuple& t:relation2.tuples)
        unionTuples.emplace(t);
    return Relation(name,scheme,unionTuples);
}

std::string Relation::toString() {
    stringstream out;
    for (Tuple t:tuples) {
        //scheme[0][0]=toupper(scheme[0][0]);
        out << "  " << scheme[0] << "=" << t[0];
        for (int i = 1; i < (int) scheme.size(); i++) {
            //scheme[i][0]=toupper(scheme[i][0]);
            out << ", " << scheme[i] << "=" << t[i];
        }
        out << endl;
    }
    return out.str();
}
