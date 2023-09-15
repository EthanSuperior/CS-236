#include <iostream>
#include "Parser.h"

#include <string>
#include <vector>
#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"

using namespace std;

void Parser::parse(const std::vector<Token>& inputTokens) {
    for (Token token:inputTokens)
        if(token.type!=Token::COMMENT)
            input.push_back(token);
    current = input.at(0);
    try {
        datalogProgram();
        cout << "Success!" << endl << program.toString();
    } catch (Token t) {
        cout << "Failure!" << endl << "  " << t.toString() << endl;
    }
}

void Parser::match(Token::TokenType next) {
    if (current.type == next)
        current = getNextToken();
    else {
        error(current);
    }
}

void Parser::error(Token current) {
    throw current;
}

Token Parser::getNextToken() {
    if(pos<input.size())
        pos++;
    return input.at(pos);
}

void Parser::datalogProgram() {
    if (current.type == Token::SCHEMES) {
        match(Token::SCHEMES);
        match(Token::COLON);
        program.Schemes.push_back(scheme());
        schemeList();
    } else
        error(current);
    if (current.type == Token::FACTS) {
        match(Token::FACTS);
        match(Token::COLON);
        factList();
    }  else
        error(current);
    if (current.type == Token::RULES) {
        match(Token::RULES);
        match(Token::COLON);
        ruleList();
    }  else
        error(current);
    if (current.type == Token::QUERIES) {
        match(Token::QUERIES);
        match(Token::COLON);
        program.Queries.push_back(query());
        queryList();
    } else
        error(current);
    if(current.type == Token::EOFile){
        return;
    } else
        error(current);
}

void Parser::schemeList() {
    if (current.type == Token::ID) {
        program.Schemes.push_back(scheme());
        schemeList();
    }
}

void Parser::factList() {
    if (current.type == Token::ID) {
        program.Facts.push_back(fact());
        factList();
    }
}

void Parser::ruleList() {
    if (current.type == Token::ID) {
        program.Rules.push_back(rule());
        ruleList();
    }
}

void Parser::queryList() {
    if (current.type == Token::ID) {
        program.Queries.push_back(query());
        queryList();
    }
}

Predicate Parser::scheme() {
    Predicate p = Predicate("");
    if (current.type == Token::ID) {
        p = Predicate(current.value);
        match(Token::ID);
        match(Token::LEFT_PAREN);
        p.prams.emplace_back(current.value);
        match(Token::ID);
        idList(p.prams);
        match(Token::RIGHT_PAREN);
    } else
        error(current);
    return p;
}

Predicate Parser::fact() {
    Predicate p = Predicate("");
    if (current.type == Token::ID) {
        p = Predicate(current.value);
        match(Token::ID);
        match(Token::LEFT_PAREN);
        program.Domain.insert(current.value);
        p.prams.emplace_back(current.value);
        match(Token::STRING);
        stringList(p.prams);
        match(Token::RIGHT_PAREN);
        match(Token::PERIOD);
    } else
        error(current);
    return p;
}

Rule Parser::rule() {
    Rule r = Rule(Predicate(""));
    if (current.type == Token::ID) {
        r.headPred = headPredicate();
        match(Token::COLON_DASH);
        r.body.push_back(predicate());
        predicateList(r.body);
        match(Token::PERIOD);
    } else
        error(current);
    return r;
}

Predicate Parser::query() {
    Predicate p = Predicate("");
    if (current.type == Token::ID) {
        p = Predicate(predicate());
        match(Token::Q_MARK);
        return p;
    } else
        error(current);
    return p;
}

Predicate Parser::headPredicate() {
    Predicate p = Predicate("");
    if (current.type == Token::ID) {
        p = Predicate(current.value);
        match(Token::ID);
        match(Token::LEFT_PAREN);
        p.prams.emplace_back(current.value);
        match(Token::ID);
        idList(p.prams);
        match(Token::RIGHT_PAREN);
    } else
        error(current);
    return p;
}

Predicate Parser::predicate() {
    Predicate p = Predicate("");
    if (current.type == Token::ID) {
        p = Predicate(current.value);
        match(Token::ID);
        match(Token::LEFT_PAREN);
        p.prams.push_back(parameter());
        parameterList(p.prams);
        match(Token::RIGHT_PAREN);
    } else
        error(current);
    return p;
}

void Parser::predicateList(std::vector<Predicate> &pred) {
    if (current.type == Token::COMMA) {
        match(Token::COMMA);
        pred.push_back(predicate());
        predicateList(pred);
    }
}

void Parser::parameterList(std::vector<Parameter> &pram) {
    if (current.type == Token::COMMA) {
        match(Token::COMMA);
        pram.push_back(parameter());
        parameterList(pram);
    }
}

void Parser::stringList(std::vector<Parameter> &pram) {
    if (current.type == Token::COMMA) {
        match(Token::COMMA);
        program.Domain.insert(current.value);
        pram.emplace_back(current.value);
        match(Token::STRING);
        stringList(pram);
    }
}

void Parser::idList(std::vector<Parameter> &pram) {
    if (current.type == Token::COMMA) {
        match(Token::COMMA);
        pram.emplace_back(current.value);
        match(Token::ID);
        idList(pram);
    }
}

Parameter Parser::parameter() {
    std::string temp = current.value;
    if (current.type == Token::STRING) { match(Token::STRING); }
    else if (current.type == Token::ID) { match(Token::ID); }
    else if (current.type == Token::LEFT_PAREN) { temp = expression(); }
    else
        error(current);
    return Parameter(temp);
}

std::string Parser::expression() {
    stringstream val;
    if (current.type == Token::LEFT_PAREN) {
        match(Token::LEFT_PAREN);
        val << "(" << parameter().value << oper() << parameter().value << ")";
        match(Token::RIGHT_PAREN);
    } else
        error(current);
    return val.str();
}

char Parser::oper() {
    if (current.type == Token::ADD) {
        match(Token::ADD);
        return '+';
    } else if (current.type == Token::MULTIPLY) {
        match(Token::MULTIPLY);
        return '*';
    } else
        error(current);
    return '\00';
}
