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
            if (unsafeIPs.contains(event.src_ip) && evaluate(event, rule)) {
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
        {"login", "basketball199", "10.0.0.13", false, "\033[32m[Low]\033[32m "},
        {"login", "mouse12", "192.168.3.22", false, "\033[33m[Medium]\033[33m "}
    };

    std::vector<Rule> rules = {
        {"Failed login detected", "success", "==", "false"}
    };

    int choice = -1;

    while (true) {
        std::cout << "\n0 - Exit\n";
        std::cout << "1 - Check alerts \n";
        std::cout << "2 - Block IPs \n";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore (1000, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        } else if (choice > 2) {
            std::cout << "Invalid choice. Try again.\n";
        }

        switch (choice) {
            case 0: std::cout << "\nExiting program.\n";
            return 0;
            case 1: std::cout << "\nChecking alerts..\n";
            processEvents(events, rules, unsafeIPs);
            break;
            case 2: {
                std::cout << "\nChecking blocked IPs...\n";
                int blockChoice = -1;

                while (true) {
                    std::cout << "The current blocked ips are: \n"; 
                    unsafeIPs.printIPs();
                    std::cout << "0 - Back to main menu\n";

                    for (int i = 0; i < events.size(); i++) {
                        std::cout << i + 1 << " - " << events[i].src_ip << "User: " << events[i].username << std::endl;
                    }

                    std::cin >> blockChoice;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore (1000, '\n');
                        std::cout << "Invalid input";
                        continue;
                    }

                    if (blockChoice == 0) {
                        std::cout << "\nReturning to menu..\n";
                        break;
                    }

                    std::string ipToBlock = events[blockChoice - 1].src_ip;

                    if (unsafeIPs.contains(ipToBlock)) {
                        std::cout << "IP already blocked.\n";
                    } else {
                        unsafeIPs.insert(ipToBlock);
                        unsafeIPs.saveToFile("blockedIPs.txt");
                        std::cout << "Blocked IP: " << ipToBlock << "\n";
                    }
                }
                break;
            }
            break;
        }
    }

    return 0;
}