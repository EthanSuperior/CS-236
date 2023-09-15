#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <vector>
#include "Token.h"
#include "DatalogProgram.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <iostream>
#include <algorithm>

class Parser {
public:
    DatalogProgram program;

    void parse(const std::vector<Token>& inputTokens);

private:
    std::vector<Token> input;

    void match(Token::TokenType next);

    static void error(Token current);

    Token getNextToken();

    Token current = Token(Token::EMPTY,"",0);

    void datalogProgram();

    void schemeList();
    void factList();
    void ruleList();
    void queryList();

    Predicate scheme();
    Predicate fact();
    Rule rule();
    Predicate query();

    Predicate headPredicate();
    Predicate predicate();

    void predicateList(std::vector<Predicate> &pred);
    void parameterList(std::vector<Parameter> &pram);
    void stringList(std::vector<Parameter> &pram);
    void idList(std::vector<Parameter> &pram);

    Parameter parameter();
    std::string expression();
    char oper();
    unsigned long pos = 0;
};


#endif //PARSER_PARSER_H
