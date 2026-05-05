#include "ExpressionBuilder.h"

void ExpressionBuilder::flushNumberBuffer() {
    if (currentInput.empty() || currentInput == "-")
        return;
    expression.push_back(std::make_shared<NumberToken>(currentInput));
    currentInput = "";
}

bool ExpressionBuilder::isUnaryMinusContext(std::string op) const {
    return (op == "-") && currentInput.empty() &&
           (expression.empty() || expression.back()->isOperator());
}

void ExpressionBuilder::appendDigit(std::string digit) {
    currentInput += digit;
}

void ExpressionBuilder::appendOperator(std::string op, int priority) {
    flushNumberBuffer();
    expression.push_back(std::make_shared<BinaryOperatorToken>(op, priority));
}

void ExpressionBuilder::appendUnaryOperator(std::string op) {
    flushNumberBuffer();
    expression.push_back(std::make_shared<UnaryOperatorToken>(op));
}

void ExpressionBuilder::appendParenthesis(std::string paren) {
    if (paren == "(" && !currentInput.empty()) {
        flushNumberBuffer();
        expression.push_back(std::make_shared<BinaryOperatorToken>("*", 2));
    }
    if (paren == ")")
        flushNumberBuffer();
    expression.push_back(std::make_shared<ParenthesisToken>(paren));
}

void ExpressionBuilder::applyUnaryFunction(std::string funcName) {
    flushNumberBuffer();
    expression.push_back(std::make_shared<UnaryOperatorToken>(funcName));
}

void ExpressionBuilder::deleteLast() {
    if (!currentInput.empty())
        currentInput.pop_back();
    else if (!expression.empty())
        expression.pop_back();
}

void ExpressionBuilder::clear() {
    expression.clear();
    currentInput = "";
}

const std::vector<std::shared_ptr<Token>>& ExpressionBuilder::getExpression() const {
    return expression;
}

std::string ExpressionBuilder::getCurrentInput() const {
    return currentInput;
}

void ExpressionBuilder::setCurrentInput(std::string input) {
    currentInput = input;
}

ExpressionBuilder::State ExpressionBuilder::saveState() const {
    return State(expression, currentInput);
}

void ExpressionBuilder::restoreState(const State& state) {
    expression = state.getExpression();
    currentInput = state.getCurrentInput();
}
