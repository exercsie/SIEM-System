#include <iostream>
#include "Logger/logger.h"

int main() {
    Event event = {"login", "bobkalamr721", "192.398.382.18", false};
    Rule rule = {"Failed login detected", "success", "==", "false", "High"};

    if (evaluate(event, rule)) {
        Alert alert = generateAlert(event, rule);
        std::cout << "[" + alert.severity << "]" << alert.message << "\n";
    } else {
        std::cout << "No alert triggered.\n";
    }

    return 0;
}