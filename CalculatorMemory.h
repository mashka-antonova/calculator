#ifndef CALCULATORMEMORY_H
#define CALCULATORMEMORY_H

class CalculatorMemory {
    double value = 0.0;
public:
    void add(double v);
    void subtract(double v);
    void clear();
    double recall() const;
    double getValue() const;
    void setValue(double v);
};

#endif // CALCULATORMEMORY_H
