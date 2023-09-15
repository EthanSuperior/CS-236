#ifndef RELATIONAL_DATABASE_INTERPRETER_H
#define RELATIONAL_DATABASE_INTERPRETER_H


#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
public:
    void makeDatabase(const DatalogProgram& input);
    void interpret(const DatalogProgram& input);
private:
    Database database;
    Relation evaluate(Predicate query, bool &variable);
};


#endif //RELATIONAL_DATABASE_INTERPRETER_H
