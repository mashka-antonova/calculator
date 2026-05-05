#include "SyVisitor.h"
#include <stdexcept>

SyVisitor::SyVisitor(std::vector<std::shared_ptr<Token>>& output,
                     std::vector<std::shared_ptr<OperatorToken>>& stack,
                     const OperationRegistry& reg)
    : output(output), stack(stack), registry(reg) {}

void SyVisitor::visit(std::shared_ptr<NumberToken> token) {
    output.push_back(token);
}

void SyVisitor::visit(std::shared_ptr<UnaryOperatorToken> token) {
    stack.push_back(token);
}

void SyVisitor::visit(std::shared_ptr<BinaryOperatorToken> token) {
    int tokenPriority = registry.getBinaryPriority(token->getValue());
    while (!stack.empty()) {
        auto top = stack.back();
        if (top->isParenthesis())
            break;
        if (top->getPriority() < tokenPriority)
            break;
        output.push_back(top);
        stack.pop_back();
    }
    stack.push_back(token);
}

void SyVisitor::visit(std::shared_ptr<ParenthesisToken> token) {
    if (token->isOpen())
        stack.push_back(token);
    else {
        bool found = false;
        while (!stack.empty()) {
            auto top = stack.back();
            stack.pop_back();
            if (top->isParenthesis()) {
                found = true;
                if (!stack.empty() && stack.back()->isUnary()) {
                    output.push_back(stack.back());
                    stack.pop_back();
                }
                break;
            }
            output.push_back(top);
        }
        if (!found)
            throw std::invalid_argument("Mismatched parentheses");
    }
}
