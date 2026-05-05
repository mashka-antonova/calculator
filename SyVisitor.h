#ifndef SYVISITOR_H
#define SYVISITOR_H

#include <vector>
#include <memory>
#include "ITokenVisitor.h"
#include "Tokens.h"
#include "OperationRegistry.h"

class SyVisitor : public ITokenVisitor {
    std::vector<std::shared_ptr<Token>>& output;
    std::vector<std::shared_ptr<OperatorToken>>& stack;
    const OperationRegistry& registry;

public:
    SyVisitor(std::vector<std::shared_ptr<Token>>& output,
              std::vector<std::shared_ptr<OperatorToken>>& stack,
              const OperationRegistry& registry);

    void visit(std::shared_ptr<NumberToken> token) override;
    void visit(std::shared_ptr<UnaryOperatorToken> token) override;
    void visit(std::shared_ptr<BinaryOperatorToken> token) override;
    void visit(std::shared_ptr<ParenthesisToken> token) override;
};

#endif // SYVISITOR_H
