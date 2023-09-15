#ifndef RELATIONAL_DATABASE_INTERPRETER_H
#define RELATIONAL_DATABASE_INTERPRETER_H


#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {
public:
    void makeDatabase(const DatalogProgram& input);
    void interpret(const DatalogProgram& input);
private:
    Database database;
    Relation evaluate(Predicate query, bool &variable);
    void evaluateQueries(const DatalogProgram &input);
    void optimizedRules(const DatalogProgram &input);
    static void DFSForest(Graph &graph);
    static void DFS(Graph &graph, const int &x, std::set<int> &scc);
};


#endif //RELATIONAL_DATABASE_INTERPRETER_H
