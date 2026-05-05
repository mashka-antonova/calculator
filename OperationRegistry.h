#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include <string>
#include <map>
#include <functional>

class OperationRegistry {
public:
    using BinaryOpFunc = std::function<double(double, double)>;
    using UnaryOpFunc = std::function<double(double)>;

    void addBinary(std::string op, int priority, BinaryOpFunc func);
    void addUnary(std::string op, UnaryOpFunc func);

    int getBinaryPriority(const std::string& op) const;
    double evaluateBinary(const std::string& op, double a, double b) const;
    double evaluateUnary(const std::string& op, double a) const;

private:
    struct BinaryOpInfo {
        int priority;
        BinaryOpFunc func;
    };
    std::map<std::string, BinaryOpInfo> binaryOps;
    std::map<std::string, UnaryOpFunc> unaryOps;
};

#endif // OPERATIONREGISTRY_H
