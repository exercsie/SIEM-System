#include "eventProcessor.h"
#include <iostream>

void processEvents(const std::vector<Event> &events, const std::vector<Rule> &rules, const IPList &unsafeIPs) {
    for (const auto &event : events) {
        if (unsafeIPs.contains(event.src_ip)) {
            std::cout << "\033[31m[!!]\033[0m Alert: Unsafe IP detected " << event.src_ip << " (User: " << event.username << ")\n";
        }
        for (const auto &rule : rules) {
            if (unsafeIPs.contains(event.src_ip) && evaluate(event, rule)) {
                Alert alert = generateAlert(event, rule);
                std::cout << alert.severity << alert.message << "\n";
            }
        }
    }
}