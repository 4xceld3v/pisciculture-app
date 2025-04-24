#ifndef POND_STATUS_EVALUATOR_H
#define POND_STATUS_EVALUATOR_H

#include <Arduino.h>
#include <domain/model/Pond.h>

class PondStatusEvaluator {
public:
    static String evaluateStatus(const Pond& data);
};

#endif
