#ifndef RELATIONAL_DATABASE_GRAPH_H
#define RELATIONAL_DATABASE_GRAPH_H

#include <map>
#include "Node.h"

class Graph : public std::map<int, Node> {
public:
    int number = 1;
};

#endif //RELATIONAL_DATABASE_GRAPH_H
