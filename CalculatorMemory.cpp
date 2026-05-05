#include "CalculatorMemory.h"

void CalculatorMemory::add(double v) {
    value += v;
}

void CalculatorMemory::subtract(double v) {
    value -= v;
}

void CalculatorMemory::clear() {
    value = 0.0;
}

double CalculatorMemory::recall() const {
    return value;
}

double CalculatorMemory::getValue() const {
    return value;
}

void CalculatorMemory::setValue(double v) {
    value = v;
}
