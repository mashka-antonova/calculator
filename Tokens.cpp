#include "Tokens.h"
#include "ITokenVisitor.h"

Token::Token(std::string val) : textValue(val) {}

std::string Token::getValue() const {
    return textValue;
}



NumberToken::NumberToken(std::string val) : Token(val) {}

bool NumberToken::isOperator() const {
    return false;
}

double NumberToken::getNumericValue() const {
    return std::stod(textValue);
}

void NumberToken::accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) {
    visitor.visit(std::static_pointer_cast<NumberToken>(self));
}




OperatorToken::OperatorToken(std::string val, int priority) : Token(val), priority(priority) {}

bool OperatorToken::isOperator() const {
    return true;
}

int OperatorToken::getPriority() const {
    return priority;
}




UnaryOperatorToken::UnaryOperatorToken(std::string val) : OperatorToken(val, 4) {}

void UnaryOperatorToken::accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) {
    visitor.visit(std::static_pointer_cast<UnaryOperatorToken>(self));
}




BinaryOperatorToken::BinaryOperatorToken(std::string val, int priority) : OperatorToken(val, priority) {}

void BinaryOperatorToken::accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) {
    visitor.visit(std::static_pointer_cast<BinaryOperatorToken>(self));
}




ParenthesisToken::ParenthesisToken(std::string val) : OperatorToken(val, 0) {}

void ParenthesisToken::accept(ITokenVisitor& visitor, std::shared_ptr<Token> self) {
    visitor.visit(std::static_pointer_cast<ParenthesisToken>(self));
}

bool ParenthesisToken::isOpen() const {
    return textValue == "(";
}


