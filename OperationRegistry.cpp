#include "OperationRegistry.h"
#include <stdexcept>

void OperationRegistry::addBinary(std::string op, int priority, BinaryOpFunc func) {
    binaryOps[op] = {priority, std::move(func)};
}

void OperationRegistry::addUnary(std::string op, UnaryOpFunc func) {
    unaryOps[op] = std::move(func);
}



int OperationRegistry::getBinaryPriority(const std::string& op) const {
    auto it = binaryOps.find(op);
    if (it == binaryOps.end())
        throw std::invalid_argument("Unknown binary operator: " + op);
    return it->second.priority;
}

double OperationRegistry::evaluateBinary(const std::string& op, double a, double b) const {
    auto it = binaryOps.find(op);
    if (it == binaryOps.end())
        throw std::invalid_argument("Unknown binary operator: " + op);
    return it->second.func(a, b);
}

double OperationRegistry::evaluateUnary(const std::string& op, double a) const {
    auto it = unaryOps.find(op);
    if (it == unaryOps.end())
        throw std::invalid_argument("Unknown unary operator: " + op);
    return it->second(a);
}
