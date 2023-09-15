#ifndef RELATIONAL_DATABASE_DATABASE_H
#define RELATIONAL_DATABASE_DATABASE_H

#include <map>
#include "Relation.h"

class Database : public std::map<std::string,Relation>{};

#endif //RELATIONAL_DATABASE_DATABASE_H
