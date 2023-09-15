#ifndef SCANNER_SCANNER_H
#define SCANNER_SCANNER_H

#include <fstream>
#include "Token.h"

using std::ifstream;
/* Regex Code for scanner:

 ('([^']|'')*')|
 ([A-Za-z][A-Za-z0-9]*)|(Facts|Schemes|Rules|Queries)|
 (:-|:|\?|\(|\)|\.|,|\*|\+)|
 (#\|[^|]*\|#)|(#[^\n]*)
|($|&|^|#\|[^|]*EOF|'([^']|'')*EOF)

 */
class Scanner {
    ifstream in;
    int lineNum = 1;
public:
    explicit Scanner(char* &filename){
        in.open(filename);
    }
    Token scanToken();
};


#endif //SCANNER_SCANNER_H
