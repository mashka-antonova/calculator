#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <vector>
#include <memory>
#include "OperationRegistry.h"
#include "EvalVisitor.h"

class Evaluator {
public:
    double evaluateRPN(const std::vector<std::shared_ptr<Token>>& rpn, const OperationRegistry& registry);
};

#endif // EVALUATOR_H
