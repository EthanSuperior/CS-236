#include <iostream>
#include <vector>
#include "Scanner.h"
#include "Parser.h"
#include "Token.h"

int main(int argc, char* argv[]) {
    if(argc<2)
        std::cout << "Please include an input file as an argument" << argc << std::endl;
    Scanner scanner = Scanner(argv[1]);
    std::vector<Token> tokens;
    while(tokens.empty() || tokens.back().type!= Token::EOFile) {
        Token token = scanner.scanToken();
        if(token.type!=Token::EMPTY)
            tokens.push_back(token);
    }
    Parser parser = Parser();
    parser.parse(tokens);
    return 0;
}
