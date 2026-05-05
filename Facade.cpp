#include "Facade.h"
#include <cctype>


Facade::Facade() : logic() {

    actionMap["+"] = [this]() { logic.appendOperator("+"); };
    actionMap["-"] = [this]() { logic.appendOperator("-"); };
    actionMap["*"] = [this]() { logic.appendOperator("*"); };
    actionMap["/"] = [this]() { logic.appendOperator("/"); };
    
    actionMap["("] = [this]() { logic.appendParenthesis("("); };
    actionMap[")"] = [this]() { logic.appendParenthesis(")"); };

    actionMap["sin"] = [this]() { logic.applyUnaryFunction("sin"); };
    actionMap["cos"] = [this]() { logic.applyUnaryFunction("cos"); };
    actionMap["tg"] = [this]() { logic.applyUnaryFunction("tg"); };
    actionMap["ctg"] = [this]() { logic.applyUnaryFunction("ctg"); };
    actionMap["sqrt"] = [this]() { logic.applyUnaryFunction("sqrt"); };
    actionMap["1/x"] = [this]() { logic.applyUnaryFunction("1/x"); };

    actionMap["="] = [this]() { logic.calculate(); };
    actionMap["C"] = [this]() { logic.clear(); };
    actionMap["Del"] = [this]() { logic.deleteLast(); };

    actionMap["M+"] = [this]() { logic.memoryAdd(); };
    actionMap["M-"] = [this]() { logic.memorySubtract(); };
    actionMap["MR"] = [this]() { logic.memoryRecall(); };
    actionMap["MC"] = [this]() { logic.memoryClear(); };
}

void Facade::pressAction(const std::string& key) {
    if (key.length() == 1 && (std::isdigit(key[0]) || key[0] == '.')) {
        history.push_back(logic.saveState());
        logic.appendDigit(key);

    } else if (actionMap.count(key)) {
        history.push_back(logic.saveState());
        actionMap[key]();
    }
}

void Facade::undo() {
    if (history.empty())
        return;
    logic.restoreState(history.back());
    history.pop_back();
}

std::string Facade::getDisplay() const {
    return logic.getDisplayText();
}
