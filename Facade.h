#ifndef FACADE_H
#define FACADE_H

#include <string>
#include "CalculatorLogic.h"
#include <vector>
#include <map>
#include <functional>

class Facade {
    CalculatorLogic logic;
    std::vector<CalculatorLogic::State> history;
    std::map<std::string, std::function<void()>> actionMap;
public:
    Facade();
    void pressAction(const std::string& key);
    void undo();
    std::string getDisplay() const;
};

#endif // FACADE_H
