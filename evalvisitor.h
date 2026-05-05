#ifndef EVALVISITOR_H
#define EVALVISITOR_H

#include <vector>
#include <memory>
#include "ITokenVisitor.h"
#include "Tokens.h"
#include "OperationRegistry.h"

class EvalVisitor : public ITokenVisitor {
    std::vector<double>& stack;
    const OperationRegistry& registry;

public:
    EvalVisitor(std::vector<double>& st, const OperationRegistry& reg);

    void visit(std::shared_ptr<NumberToken> token) override;
    void visit(std::shared_ptr<UnaryOperatorToken> token) override;
    void visit(std::shared_ptr<BinaryOperatorToken> token) override;
    void visit(std::shared_ptr<ParenthesisToken> token) override;
};

#endif // EVALVISITOR_H
