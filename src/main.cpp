#include <iostream>
#include <vector>
#include "Logger/logger.h"

int main() {
    std::vector<Event> events = {
        {"login", "bonnieMaster922", "192.168.32.2", false},
        {"login", "basketball199", "192.168.92.3", false},
        {"login", "mouse12", "192.168.3.22", false}
    };

    std::vector<Rule> rules = {
        {"Failed login detected", "success", "==", "false", "High"}
    };

    for (const auto &event : events) {
        for (const auto &rule : rules) {
            if (evaluate(event, rule)) {
                Alert alert = generateAlert(event, rule);
                std::cout << "[" << alert.severity << "]" << alert.message << "\n";
            }
        }
    }

    return 0;
}