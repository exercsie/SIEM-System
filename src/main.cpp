#include <iostream>
#include <vector>
#include "Logger/logger.h"
#include "Logger/IPList.h"
#include "Menu/menu.h"
#include "Event_Processor/eventProcessor.h"

int main() {
    IPList unsafeIPs;
    unsafeIPs.loadFromFile("Files/unsafeIPList.txt");

    IPList blockedIPs;
    blockedIPs.loadFromFile("Files/blockedIPs.txt");

    std::vector<Event> events = {
        {"login", "bonnieMaster922", "192.168.32.2", false, "\033[31m[High]\033[31m "},
        {"login", "basketball199", "29.3881.283", false, "\033[32m[Low]\033[32m "},
        {"login", "mouse12", "192.168.3.22", false, "\033[33m[Medium]\033[33m "}
    };

    std::vector<Rule> rules = {
        {"Failed login detected", "success", "==", "false"}
    };

    menu(unsafeIPs, blockedIPs, events, rules);

    return 0;
}