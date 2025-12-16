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

    std::vector<Event> events = loadEventFile("Files/events.txt");

    std::vector<Rule> rules = {
        {"Failed login detected", "success", "==", "false"}
    };

    menu(unsafeIPs, blockedIPs, events, rules);

    return 0;
}