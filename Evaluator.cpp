#include "Evaluator.h"
#include <stdexcept>

double Evaluator::evaluateRPN(const std::vector<std::shared_ptr<Token>>& rpn, const OperationRegistry& registry) {
    std::vector<double> stack;
    EvalVisitor visitor(stack, registry);

    for (const auto& token : rpn)
        token->accept(visitor, token);

    if (stack.size() != 1)
        throw std::invalid_argument("Invalid expression");

    return stack.back();
}
