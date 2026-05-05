#include "EvalVisitor.h"
#include <stdexcept>

EvalVisitor::EvalVisitor(std::vector<double>& st, const OperationRegistry& reg)
    : stack(st), registry(reg) {}

void EvalVisitor::visit(std::shared_ptr<NumberToken> token) {
    stack.push_back(token->getNumericValue());
}

void EvalVisitor::visit(std::shared_ptr<UnaryOperatorToken> token) {
    if (stack.empty())
        throw std::invalid_argument("Invalid expression");
    double val = stack.back();
    stack.pop_back();
    stack.push_back(registry.evaluateUnary(token->getValue(), val));
}

void EvalVisitor::visit(std::shared_ptr<BinaryOperatorToken> token) {
    if (stack.size() < 2)
        throw std::invalid_argument("Invalid expression");
    double b = stack.back();
    stack.pop_back();
    double a = stack.back();
    stack.pop_back();
    stack.push_back(registry.evaluateBinary(token->getValue(), a, b));
}

void EvalVisitor::visit(std::shared_ptr<ParenthesisToken> token) {
    throw std::invalid_argument("Invalid expression");
}
