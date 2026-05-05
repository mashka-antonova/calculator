#ifndef CALCULATORLOGIC_H
#define CALCULATORLOGIC_H

#include <string>
#include "OperationRegistry.h"
#include "CalculatorMemory.h"
#include "ExpressionBuilder.h"


class CalculatorLogic {
public:
    class State {
    private:
        ExpressionBuilder::State builderState;
        double memoryValue = 0.0;
    public:
        State() = default;
        State(ExpressionBuilder::State bState, double mVal)
            : builderState(std::move(bState)), memoryValue(mVal) {}

        ExpressionBuilder::State getBuilderState() const {
            return builderState;
        }
        double getMemoryValue() const {
            return memoryValue;
        }
    };

private:
    ExpressionBuilder builder;
    CalculatorMemory memory;
    std::string errorMessage;
    OperationRegistry registry;

public:
    CalculatorLogic();

    void appendDigit(std::string digit);
    void appendOperator(std::string op);
    void appendParenthesis(std::string paren);
    void applyUnaryFunction(std::string funcName);
    void calculate();
    void clear();
    void deleteLast();

    void memoryAdd();
    void memorySubtract();
    void memoryRecall();
    void memoryClear();

    std::string getDisplayText() const;
    State saveState() const;
    void restoreState(const State& state);

    const OperationRegistry& getRegistry() const {
        return registry;
    }

private:
    void setError(std::string msg);
    void clearError();
    bool hasError() const;
    double evaluateExpression();
    std::string formatDouble(double val) const;
    void setupRegistry();
};

#endif // CALCULATORLOGIC_H
