#ifndef ITOKENVISITOR_H
#define ITOKENVISITOR_H

#include <memory>

class NumberToken;
class BinaryOperatorToken;
class UnaryOperatorToken;
class ParenthesisToken;

class ITokenVisitor {
public:
    virtual ~ITokenVisitor() = default;

    virtual void visit(std::shared_ptr<NumberToken> token) = 0;
    virtual void visit(std::shared_ptr<BinaryOperatorToken> token) = 0;
    virtual void visit(std::shared_ptr<UnaryOperatorToken> token) = 0;
    virtual void visit(std::shared_ptr<ParenthesisToken> token) = 0;
};

#endif // ITOKENVISITOR_H
