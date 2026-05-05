#include "CalculatorLogic.h"
#include "ShuntingYard.h"
#include "Evaluator.h"
#include <cmath>
#include <stdexcept>


std::string CalculatorLogic::formatDouble(double val) const {
    std::string str = std::to_string(val);
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (!str.empty() && str.back() == '.')
        str.pop_back();
    return str;
}

CalculatorLogic::CalculatorLogic() {
    setupRegistry();
}

void CalculatorLogic::setupRegistry() {

    registry.addBinary("+", 1, [](double x, double y) { return x + y; });
    registry.addBinary("-", 1, [](double x, double y) { return x - y; });
    registry.addBinary("*", 2, [](double x, double y) { return x * y; });
    registry.addBinary("/", 2, [](double x, double y) {
        if (std::abs(y) < 1e-9) throw std::invalid_argument("Division by zero");
            return x / y;
    });


    registry.addUnary("-", [](double x) { return -x; });
    registry.addUnary("sqrt", [](double v) {
        if (v < 0) throw std::invalid_argument("sqrt(<0)");
            return std::sqrt(v);
    });
    registry.addUnary("1/x", [](double v) {
        if (std::abs(v) < 1e-9) throw std::invalid_argument("1/0");
            return 1.0 / v;
    });


    auto toRad = [](double deg) { return deg * std::numbers::pi / 180.0; };

    registry.addUnary("sin", [toRad](double v) { return std::sin(toRad(v)); });
    registry.addUnary("cos", [toRad](double v) { return std::cos(toRad(v)); });
    registry.addUnary("tg",  [toRad](double v) { return std::tan(toRad(v)); });
    registry.addUnary("ctg", [toRad](double v) {
        double t = std::tan(toRad(v));
        if (std::abs(t) < 1e-9) throw std::invalid_argument("ctg(0)");
            return 1.0 / t;
    });
}

CalculatorLogic::State CalculatorLogic::saveState() const {
    return State(builder.saveState(), memory.getValue());
}

void CalculatorLogic::restoreState(const State& state) {
    builder.restoreState(state.getBuilderState());
    clearError();
    memory.setValue(state.getMemoryValue());
}

void CalculatorLogic::setError(std::string msg) {
    errorMessage = msg;
}

void CalculatorLogic::clearError() {
    errorMessage = "";
}

bool CalculatorLogic::hasError() const {
    return !errorMessage.empty();
}

void CalculatorLogic::appendDigit(std::string digit) {
    if (hasError())
        clear();
    builder.appendDigit(digit);
}

void CalculatorLogic::appendOperator(std::string op) {
    if (hasError())
        clear();
    if (builder.isUnaryMinusContext(op)) {
        builder.appendUnaryOperator("-");
        return;
    }
    builder.appendOperator(op, registry.getBinaryPriority(op));
}

void CalculatorLogic::appendParenthesis(std::string paren) {
    if (hasError())
        clear();
    builder.appendParenthesis(paren);
}

void CalculatorLogic::applyUnaryFunction(std::string funcName) {
    if (hasError())
        clear();
    builder.applyUnaryFunction(funcName);
}

void CalculatorLogic::clear() {
    builder.clear();
    clearError();
}

void CalculatorLogic::deleteLast() {
    if (hasError()) {
        clear();
        return;
    }
    builder.deleteLast();
}

double CalculatorLogic::evaluateExpression() {
    ShuntingYard sy;
    auto rpn = sy.convertToRPN(builder.getExpression(), registry);
    Evaluator evaluator;
    return evaluator.evaluateRPN(rpn, registry);
}

void CalculatorLogic::calculate() {
    if (hasError())
        clear();
    builder.flushNumberBuffer();
    if (builder.getExpression().empty())
        return;
    try {
        double result = evaluateExpression();
        clear();
        builder.setCurrentInput(formatDouble(result));
    } catch (const std::exception& e) {
        setError(e.what());
    }
}

std::string CalculatorLogic::getDisplayText() const {
    if (hasError())
        return errorMessage;
    std::string text = "";
    for (const auto& t : builder.getExpression())
        text += t->getValue() + " ";
    text += builder.getCurrentInput();
    return text;
}

void CalculatorLogic::memoryAdd() {
    if (!builder.getExpression().empty()) {
        setError("Cannot save expression to memory");
        return;
    }
    std::string currentInput = builder.getCurrentInput();
    if (!currentInput.empty() && currentInput != "-")
        memory.add(std::stod(currentInput));
}

void CalculatorLogic::memorySubtract() {
    if (!builder.getExpression().empty()) {
        setError("Cannot save expression to memory");
        return;
    }
    std::string currentInput = builder.getCurrentInput();
    if (!currentInput.empty() && currentInput != "-")
        memory.subtract(std::stod(currentInput));
}

void CalculatorLogic::memoryRecall() {
    if (hasError())
        clear();
    builder.setCurrentInput(formatDouble(memory.recall()));
}

void CalculatorLogic::memoryClear() {
    memory.clear();
}
