#include "Scanner.h"
#include <string>
#include <iostream>

using std::string;

Token Scanner::scanToken() {
    int nextChar = in.get();
    std::stringstream temp;
    int lnum = lineNum;
    if (nextChar == -1)
        return Token(Token::EOFile, "", lineNum);
    else if (nextChar == '\n') {
        lineNum++;
        return Token(Token::EMPTY, "", 0);
    }
    else if (isspace(nextChar))
        return Token(Token::EMPTY, "", 0);
    else if (nextChar == '\'') {
        temp << (char) nextChar;
        nextChar = in.get();
        while (nextChar != EOF && (nextChar != '\'' || in.peek() == '\'')) {
            temp << (char) nextChar;
            if (nextChar == '\'') {
                temp << (char) in.get();
            } else if(nextChar == '\n')
                lineNum++;
            nextChar = in.get();
        }
        if (nextChar == EOF)
            return Token(Token::UNDEFINED, temp.str(), lnum);
        temp << (char) nextChar;
        return Token(Token::STRING, temp.str(), lnum);
    } else if ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z')) {
        temp << (char) nextChar;
        nextChar = in.peek();
        while ((nextChar >= 'a' && nextChar <= 'z') || (nextChar >= 'A' && nextChar <= 'Z') ||
               (nextChar >= '0' && nextChar <= '9')) {
            temp << (char) in.get();
            nextChar = in.peek();
        }
        if (temp.str() == "Facts")
            return Token(Token::FACTS, "Facts", lineNum);
        else if (temp.str() == "Schemes")
            return Token(Token::SCHEMES, "Schemes", lineNum);
        else if (temp.str() == "Rules")
            return Token(Token::RULES, "Rules", lineNum);
        else if (temp.str() == "Queries")
            return Token(Token::QUERIES, "Queries", lineNum);
        return Token(Token::ID, temp.str(), lnum);
    } else if (nextChar == '#') {
        temp << (char) nextChar;
        nextChar = in.peek();
        //case 1: multi line comment
        if(nextChar == '|'){
            temp << (char) in.get();
            nextChar = in.get();
            while (!(nextChar == '|' && in.peek()=='#')) {
                temp << (char) nextChar;
                if(nextChar == '\n')
                    lineNum++;
                nextChar = in.get();
                if(nextChar == EOF){ // Unterminated Comment
                    return Token(Token::UNDEFINED, temp.str(), lnum);
                }
            }
            temp << (char) nextChar << (char)in.get();
        } else { // single line
            while (nextChar != 13 && nextChar != '\n' && nextChar != EOF) {
                temp << (char) in.get();
                nextChar = in.peek();
            }
        }
        return Token(Token::COMMENT, temp.str(), lnum);
    } else if (nextChar == ':') {
        if (in.peek() == '-') {
            in.get();
            return Token(Token::COLON_DASH, ":-", lineNum);
        }
        return Token(Token::COLON, ":", lineNum);
    } else if (nextChar == '?') {
        return Token(Token::Q_MARK, "?", lineNum);
    } else if (nextChar == '(') {
        return Token(Token::LEFT_PAREN, "(", lineNum);
    } else if (nextChar == ')') {
        return Token(Token::RIGHT_PAREN, ")", lineNum);
    } else if (nextChar == '.') {
        return Token(Token::PERIOD, ".", lineNum);
    } else if (nextChar == ',') {
        return Token(Token::COMMA, ",", lineNum);
    } else if (nextChar == '*') {
        return Token(Token::MULTIPLY, "*", lineNum);
    } else if (nextChar == '+') {
        return Token(Token::ADD, "+", lineNum);
    } else{
        temp << (char) nextChar;
        return Token(Token::UNDEFINED, temp.str(), lnum);
    }
}