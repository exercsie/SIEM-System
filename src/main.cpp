#include <iostream>
#include <vector>
#include "Logger/logger.h"
#include "Logger/IPList.h"

void processEvents(const std::vector<Event> &events, const std::vector<Rule> &rules, const IPList &unsafeIPs) {
    for (const auto &event : events) {
        if (unsafeIPs.contains(event.src_ip)) {
            std::cout << "\033[31m[!!]\033[0m Alert: Unsafe IP detected " << event.src_ip << " (User: " << event.username << ")\n";
        }
        for (const auto &rule : rules) {
            if (evaluate(event, rule)) {
                Alert alert = generateAlert(event, rule);
                std::cout << alert.severity << alert.message << "\n";
            }
        }
    }
}

int main() {
    IPList unsafeIPs;
    unsafeIPs.loadFromFile("unsafeIPList.txt");

    std::vector<Event> events = {
        {"login", "bonnieMaster922", "192.168.32.2", false, "\033[31m[High]\033[31m "},
        {"login", "basketball199", "192.168.92.3", false, "\033[32m[Low]\033[32m "},
        {"login", "mouse12", "192.168.3.22", false, "\033[33m[Medium]\033[33m "}
    };

    std::vector<Rule> rules = {
        {"Failed login detected", "success", "==", "false"}
    };

    int choice = -1;

    while (true) {
        std::cout << "0 - Exit\n";
        std::cout << "1 - Check alerts \n";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore (1000, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 1) {
            std::cout << "\nChecking alerts..\n";
            processEvents(events, rules, unsafeIPs);
        } else if (choice == 0) {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}