#ifndef EXPRESSIONBUILDER_H
#define EXPRESSIONBUILDER_H

#include <string>
#include <vector>
#include <memory>
#include "Tokens.h"

class ExpressionBuilder {
public:
    class State {
    private:
        std::vector<std::shared_ptr<Token>> expression;
        std::string currentInput;
    public:
        State() = default;
        State(std::vector<std::shared_ptr<Token>> expr, std::string input)
            : expression(std::move(expr)), currentInput(std::move(input)) {}

        const std::vector<std::shared_ptr<Token>>& getExpression() const {
            return expression;
        }
        std::string getCurrentInput() const {
            return currentInput;
        }
    };

    void appendDigit(std::string digit);
    void appendOperator(std::string op, int priority);
    void appendUnaryOperator(std::string op);
    void appendParenthesis(std::string paren);
    void applyUnaryFunction(std::string funcName);
    void deleteLast();
    void clear();
    void flushNumberBuffer();

    const std::vector<std::shared_ptr<Token>>& getExpression() const;
    std::string getCurrentInput() const;
    void setCurrentInput(std::string input);

    bool isUnaryMinusContext(std::string op) const;

    State saveState() const;
    void restoreState(const State& state);

private:
    std::vector<std::shared_ptr<Token>> expression;
    std::string currentInput;

};

#endif // EXPRESSIONBUILDER_H
