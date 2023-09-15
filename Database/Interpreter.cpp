#include <iostream>
#include "Interpreter.h"

void Interpreter::makeDatabase(const DatalogProgram &input) {
    for (const Predicate &scheme:input.Schemes) {
        Scheme newScheme;
        for (const Parameter &param:scheme.prams)
            newScheme.push_back(param.value);
        database.emplace(std::pair<std::string, Relation>(scheme.name, Relation(scheme.name, newScheme)));
    }
    for (const Predicate &facts:input.Facts) {
        Tuple newTuple;
        for (const Parameter &param:facts.prams)
            newTuple.push_back(param.value);
        database[facts.name].tuples.emplace(newTuple);
    }
}

void Interpreter::interpret(const DatalogProgram &input) {
    makeDatabase(input);
    for (Predicate query:input.Queries) {
        bool var = false;
        Relation relation = evaluate(query, var);
        if (relation.tuples.empty())
            std::cout << query.toString() << "? No" << std::endl;
        else {
            std::cout << query.toString() << "? Yes(" << relation.tuples.size() << ")" << std::endl;
            if(var)
                std::cout << relation.toString();
        }
    }
}

Relation Interpreter::evaluate(Predicate query, bool &variable) {
    Relation relation = database[query.name];
    std::set<int> columnList;
    std::set<int> duplicateColumnList;
    for (int index = 0; index < (int)query.prams.size(); index++)
        if (query.prams[index].value[0] == '\'') {
            relation = relation.select(index, query.prams[index].value);
        } else { // Variable, check to see if there is duplicate;
            variable = true;
            for (int i = index + 1; i < (int)query.prams.size(); i++)
                if (query.prams[index].value == query.prams[i].value) {
                    relation = relation.select(index, i);
                    duplicateColumnList.emplace(i);
                }
        }
    for (int index = 0; index < (int)query.prams.size(); index++)
        if (query.prams[index].value[0] != '\'')
            columnList.emplace(index);
    for(int dup:duplicateColumnList)
        columnList.erase(dup);
    if(variable) {
        relation = relation.project(columnList);
        int j=0;
        for (auto i = columnList.begin(); i!=columnList.end();i++) {
            relation = relation.rename(j, query.prams[*i].value);
            j++;
        }
    }
    return relation;
}
