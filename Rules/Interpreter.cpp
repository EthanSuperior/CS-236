#include <iostream>
#include "Interpreter.h"







void Interpreter::makeDatabase(const DatalogProgram &input) {
    for (const Predicate &scheme:input.Schemes) {
        Scheme newScheme;
        for (const Parameter &param:scheme.prams)
            newScheme.push_back(param.value);
		database.insert(std::pair<string, Relation>(pred.getName(), r))
        database.emplace(std::pair<std::string, Relation>(scheme.name, Relation(scheme.name, newScheme)));
    }
    for (const Predicate &facts:input.Facts) {
        Tuple newTuple;
        for (const Parameter &param:facts.prams)
            newTuple.push_back(param.value);
        database[facts.name].tuples.emplace(newTuple);
    }
    bool updatedDatabase = true;
    int numPasses = 0;
    std::cout << "Rule Evaluation" << std::endl;
    while (updatedDatabase) {
        updatedDatabase = false;
        bool successfulQuery = false;
        for (Rule rules:input.Rules) {
            Relation newTuples = Relation();
            //Join the Rule's Predicates
            for (const Predicate &pred:rules.body) {
                Relation temp = evaluate(pred, successfulQuery);
                newTuples = newTuples.join(temp);
            }
            //Project it to match the Rule
            Scheme ruleScheme = evaluate(rules.headPred, successfulQuery).scheme;
            std::vector<int> columnList;
            for (const std::string &colName:ruleScheme)
                for (int index = 0; index < (int) newTuples.scheme.size(); index++)
                    if (colName == newTuples.scheme.at(index))
                        columnList.push_back(index);
            newTuples = newTuples.project(columnList);
            bool changed = true;
            while (changed) {
                changed = false;
                for (const Tuple &t:database[rules.headPred.name].tuples) {
                    for (auto i = newTuples.tuples.begin(); i != newTuples.tuples.end(); i++)
                        if (t == *i) {
                            newTuples.tuples.erase(i);
                            changed = true;
                            break;
                        }
                    if (changed)
                        break;
                }
            }
            //Rename before union;
            newTuples.scheme = database[rules.headPred.name].scheme;
            std::cout << rules.toString() << "." << std::endl << newTuples.toString();
            //Union && CheckforUpdates;
            int oldSize = (int) database[rules.headPred.name].tuples.size();
            database[rules.headPred.name] = database[rules.headPred.name].Union(newTuples);
            updatedDatabase = updatedDatabase || (oldSize != (int) database[rules.headPred.name].tuples.size());
        }
        numPasses++;
    }
    std::cout << std::endl << "Schemes populated after " << numPasses << " passes through the Rules." << std::endl
              << std::endl;
}

void Interpreter::interpret(const DatalogProgram &input) {
    makeDatabase(input);
    std::cout << "Query Evaluation" << std::endl;
    for (Predicate query:input.Queries) {
        bool var = false;
        Relation relation = evaluate(query, var);
        if (relation.tuples.empty())
            std::cout << query.toString() << "? No" << std::endl;
        else {
            std::cout << query.toString() << "? Yes(" << relation.tuples.size() << ")" << std::endl;
            if (var)
                std::cout << relation.toString();
        }
    }
    //std::cout<<std::endl<<"DATABASE:"<<std::endl<<database.toString();//TODO:DEBUG
}

Relation Interpreter::evaluate(Predicate query, bool &variable) {
    Relation relation = database[query.name];
    std::vector<int> columnList;
    std::set<int> duplicateColumnList;
    for (int index = 0; index < (int) query.prams.size(); index++)
        if (query.prams[index].value[0] == '\'') {
            relation = relation.select(index, query.prams[index].value);
        } else { // Variable, check to see if there is duplicate;
            variable = true;
            for (int i = index + 1; i < (int) query.prams.size(); i++)
                if (query.prams[index].value == query.prams[i].value) {
                    relation = relation.select(index, i);
                    duplicateColumnList.emplace(i);
                }
        }
    for (int index = 0; index < (int) query.prams.size(); index++) {
        if (query.prams[index].value[0] != '\'') {
            columnList.push_back(index);
            for (int dup:duplicateColumnList)
                if (dup == index) {
                    columnList.pop_back();
                    break;
                }
        }
    }
    if (variable) {
        relation = relation.project(columnList);
        int j = 0;
        for (int &i : columnList) {
            relation = relation.rename(j, query.prams[i].value);
            j++;
        }
    }
    return relation;
}
