#ifndef SCANNER_TOKEN_H
#define SCANNER_TOKEN_H


#include <string>
#include <utility>
#include <sstream>

class Token {
public:
    enum TokenType{COMMA,PERIOD,Q_MARK,LEFT_PAREN,RIGHT_PAREN,COLON,COLON_DASH,MULTIPLY,ADD,SCHEMES,FACTS,RULES,QUERIES,ID,STRING,COMMENT,UNDEFINED,EOFile,EMPTY};
    TokenType  type = static_cast<TokenType>(30);
    std::string value;
    int lineNumber;
    explicit Token(TokenType ty = COMMA, std::string val =",", int lnum = 1){
        type=ty;
        value=std::move(val);
        lineNumber=lnum;
    }
    std::string toString() {
        std::stringstream out;
        switch (type) {
            case COMMA:
                out << "(COMMA,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case PERIOD:
                out << "(PERIOD,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case Q_MARK:
                out << "(Q_MARK,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case LEFT_PAREN:
                out << "(LEFT_PAREN,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case RIGHT_PAREN:
                out << "(RIGHT_PAREN,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case COLON:
                out << "(COLON,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case COLON_DASH:
                out << "(COLON_DASH,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case MULTIPLY:
                out << "(MULTIPLY,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case ADD:
                out << "(ADD,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case SCHEMES:
                out << "(SCHEMES,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case FACTS:
                out << "(FACTS,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case RULES:
                out << "(RULES,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case QUERIES:
                out << "(QUERIES,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case ID:
                out << "(ID,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case STRING:
                out << "(STRING,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case COMMENT:
                out << "(COMMENT,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
            case EOFile:
                out << "(EOF,\"\","<<std::to_string(lineNumber)<<")";
                break;
            default:
                out << "(UNDEFINED,\"" << value << "\","<<std::to_string(lineNumber)<<")";
                break;
        }
        return out.str();
    }
};


#endif //SCANNER_TOKEN_H
