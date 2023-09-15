#include <iostream>
#include "Interpreter.h"
#include "Graph.h"

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
    optimizedRules(input);
    evaluateQueries(input);
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

void Interpreter::evaluateQueries(const DatalogProgram &input) {
    std::cout << std::endl << "Query Evaluation" << std::endl;
    for (const Predicate &query:input.Queries) {
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
}

void Interpreter::optimizedRules(const DatalogProgram &input) {
    Graph ruleGraph = Graph();
    Graph reverseGraph = Graph();
    std::cout << "Dependency Graph";
    for (int i = 0; i < (int) input.Rules.size(); i++) {
        ruleGraph.insert(std::pair<int, Node>(i, Node(i)));
        reverseGraph.insert(std::pair<int, Node>(i, Node(i)));
    }
    for (int i = 0; i < (int) input.Rules.size(); i++)
        for (const Predicate &pred:input.Rules[i].body)
            for (int j = 0; j < (int) input.Rules.size(); j++)
                if (pred.name == input.Rules[j].headPred.name) {
                    ruleGraph[i].dependencies.insert(j);
                    reverseGraph[j].dependencies.insert(i);
                }
    for (int i = 0; i < (int) ruleGraph.size(); i++) {
        std::cout << std::endl << "R" << i << ":";
        for (int id:ruleGraph[i].dependencies)
            if (id == *ruleGraph[i].dependencies.begin())
                std::cout << "R" << id;
            else
                std::cout << ",R" << id;
    }
    DFSForest(reverseGraph);
    std::vector<int> topologicalSort;
    while (topologicalSort.size() != reverseGraph.size())
        for (const auto &i:reverseGraph)
            if (i.second.postOrder == (int) (reverseGraph.size() - topologicalSort.size()))
                topologicalSort.push_back(i.second.id);
    std::cout << std::endl << std::endl << "Rule Evaluation" << std::endl;
    for (int id:topologicalSort) {
        std::set<int> scc;
        if (!ruleGraph[id].visited) {
            DFS(ruleGraph, id, scc);
            std::cout << "SCC: ";
            for(int j:scc) {
                if (j!=*scc.begin())
                    std::cout << ",";
                std::cout << "R" << j;
            }
            std::cout << std::endl;
            bool updatedDatabase = true;
            int numPasses = 0;
            while (updatedDatabase) {
                updatedDatabase = false;
                bool successfulQuery = false;
                for (int sccID:scc) {
                    Relation newTuples = Relation();
                    //Join the Rule's Predicates
                    for (const Predicate &pred:input.Rules[sccID].body) {
                        Relation temp = evaluate(pred, successfulQuery);
                        newTuples = newTuples.join(temp);
                    }
                    //Project it to match the Rule
                    Scheme ruleScheme = evaluate(input.Rules[sccID].headPred, successfulQuery).scheme;
                    std::vector<int> columnList;
                    for (const std::string &colName:ruleScheme)
                        for (int index = 0; index < (int) newTuples.scheme.size(); index++)
                            if (colName == newTuples.scheme.at(index))
                                columnList.push_back(index);
                    newTuples = newTuples.project(columnList);
                    bool changed = true;
                    while (changed) {
                        changed = false;
                        for (const Tuple &t:database[input.Rules[sccID].headPred.name].tuples) {
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
                    newTuples.scheme = database[input.Rules[sccID].headPred.name].scheme;
                    std::cout << input.Rules[sccID].toString() << "." << std::endl << newTuples.toString();
                    //Union && Check for Updates;
                    int oldSize = (int) database[input.Rules[sccID].headPred.name].tuples.size();
                    database[input.Rules[sccID].headPred.name] = database[input.Rules[sccID].headPred.name].Union(
                            newTuples);
                    updatedDatabase = updatedDatabase ||
                                      (oldSize != (int) database[input.Rules[sccID].headPred.name].tuples.size());
                }
                numPasses++;
                //Added check to break early if there is only one rule and its not self-dependent
                if (scc.size() == 1) {
                    bool selfDependent = false;
                    for (auto a:ruleGraph[*scc.begin()].dependencies)
                        if (a == *scc.begin())
                            selfDependent = true;
                    if (!selfDependent)
                        updatedDatabase = false;
                }
            }
            std::cout << numPasses << " passes: ";
            for(int j:scc) {
                if (j!=*scc.begin())
                    std::cout << ",";
                std::cout << "R" << j;
            }
            std::cout << std::endl;
        }
    }
}

void Interpreter::DFSForest(Graph &graph) {
    graph.number = 1;
    for (auto i: graph) {
        i.second.visited = false;
        i.second.postOrder = 0;
    }
    std::set<int> a;
    for (const auto &i: graph)
        if (!i.second.visited)
            DFS(graph, i.second.id, a);
}

void Interpreter::DFS(Graph &graph, const int &x, std::set<int> &scc) {
    graph[x].visited = true;
    scc.emplace(x);
    for (int y:graph[x].dependencies)
        if (!graph[y].visited)
            DFS(graph, y, scc);
    graph[x].postOrder = graph.number++;
}