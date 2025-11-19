#include <iostream>
#include <vector>
#include "Logger/logger.h"
#include "Logger/IPList.h"

void processEvents(const std::vector<Event> &events, const std::vector<Rule> &rules, const IPList &unsafeIPs) {
    for (const auto &event : events) {
        if (unsafeIPs.contains(event.src_ip)) {
            std::cout << "[!!] ALERET: Unsafe IP detected " << event.src_ip << " (User: " << event.username << ")\n";
        }
        for (const auto &rule : rules) {
            if (evaluate(event, rule)) {
                Alert alert = generateAlert(event, rule);
                std::cout << "[" << alert.severity << "]" << alert.message << "\n";
            }
        }
    }
}

int main() {
    std::vector<Event> events = {
        {"login", "bonnieMaster922", "192.168.32.2", false, "High"},
        {"login", "basketball199", "192.168.92.3", false, "Low"},
        {"login", "mouse12", "192.168.3.22", false, "Medium"}
    };

    std::vector<Rule> rules = {
        {"Failed login detected", "success", "==", "false"}
    };

    processEvents(events, rules);

    return 0;
}