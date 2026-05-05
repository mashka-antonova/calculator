#include "ShuntingYard.h"
#include <stdexcept>

std::vector<std::shared_ptr<Token>> ShuntingYard::convertToRPN(const std::vector<std::shared_ptr<Token>>& infix,
                                                               const OperationRegistry& registry)
{
    std::vector<std::shared_ptr<Token>> output;
    std::vector<std::shared_ptr<OperatorToken>> stack;
    SyVisitor visitor(output, stack, registry);

    for (const auto& token : infix)
        token->accept(visitor, token);

    while (!stack.empty()) {
        auto top = stack.back();
        if (top->isParenthesis())
            throw std::invalid_argument("Mismatched parentheses");
        output.push_back(top);
        stack.pop_back();
    }
    return output;
}
