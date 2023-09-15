#ifndef RELATIONAL_DATABASE_NODE_H
#define RELATIONAL_DATABASE_NODE_H

#include <set>

class Node {
public:
    Node(){id=0;}
    explicit Node(int ID){id=ID;}
    int id;
    std::set<int> dependencies;
    bool visited = false;
    int postOrder = -1;
};


#endif //RELATIONAL_DATABASE_NODE_H
