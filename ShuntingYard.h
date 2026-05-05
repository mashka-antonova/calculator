#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <vector>
#include <memory>
#include "SyVisitor.h"
#include "OperationRegistry.h"

class ShuntingYard {
public:
    std::vector<std::shared_ptr<Token>> convertToRPN(const std::vector<std::shared_ptr<Token>>& infix, const OperationRegistry& registry);
};

#endif // SHUNTINGYARD_H
