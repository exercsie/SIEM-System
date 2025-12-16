#include "logger.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <regex>

bool evaluate(const Event &e, const Rule &r) {
    if (r.field == "success" && r.op == "==") {
        bool val = (r.value == "true");
        return e.success == val;
    }
    return false;
}

Alert generateAlert(const Event &e, const Rule &r) {
    Alert a;
    a.name = r.name;
    a.severity = e.severity;
    a.message = "\033[0mAlert: \033[0m" + r.name + " User: " + e.username + " IP: " + e.src_ip;
    return a;
}

std::vector<Event> loadEventFile(const std::string &filename) {
    std::vector<Event> events;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "File cannot open\n";
        return events;
    }

    std::string chars;
    while (std::getline(file, chars)) {
        if (chars.empty()) {
            continue;
        }

        std::stringstream x(chars);
        Event event;
        std::string stringWorked;

        if (std::getline(x, event.event_type, ',') && std::getline(x, event.username, ',') && std::getline(x, event.src_ip, ',') 
        && std::getline(x, stringWorked, ',') && std::getline (x, event.severity)) {
            event.success = (stringWorked == "true");
            event.severity = std::regex_replace(event.severity, std::regex("\\\\033"), "\033");
            events.push_back(event);
        }
    }
    return events;    
}