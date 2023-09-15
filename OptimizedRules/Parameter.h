#include <utility>
#include <string>

#ifndef PARSER_PARAMETER_H
#define PARSER_PARAMETER_H

class Parameter {
public:
    std::string value;

    std::string toString() const {
        return value;
    }

    explicit Parameter(std::string exp) {
        value = std::move(exp);
    }

    Parameter() = default;
};

#endif //PARSER_PARAMETER_H
