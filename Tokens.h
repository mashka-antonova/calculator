#include <string>
#include <memory>

#ifndef TOKENS_H
#define TOKENS_H

class ITokenVisitor;

class Token {
protected:
    std::string textValue;
public:
    explicit Token(std::string val);
    virtual ~Token() = default;

    std::string getValue() const;
    virtual bool isOperator() const = 0;
    virtual void accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) = 0;
};




class NumberToken : public Token {
public:
    explicit NumberToken(std::string val);
    bool isOperator() const override;
    double getNumericValue() const;
    void accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) override;
};

class OperatorToken : public Token {
protected:
    int priority;
public:
    OperatorToken(std::string val, int priority);
    bool isOperator() const override;
    int getPriority() const;

    virtual bool isParenthesis() const { //
        return false;
    }
    virtual bool isUnary() const {
        return false;
    }
};




class UnaryOperatorToken : public OperatorToken {
public:
    explicit UnaryOperatorToken(std::string val);
    void accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) override;
    bool isUnary() const override {
        return true;
    }
};

class BinaryOperatorToken : public OperatorToken {
public:
    BinaryOperatorToken(std::string val, int priority);
    void accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) override;
};

class ParenthesisToken : public OperatorToken {
public:
    explicit ParenthesisToken(std::string val);
    bool isOpen() const;

    void accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) override;

    bool isParenthesis() const override {
        return true;
    }
};

#endif
