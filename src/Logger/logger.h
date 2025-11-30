#pragma once
#include <string>

struct Event {
    std::string event_type;
    std::string username;
    std::string src_ip;
    bool success;
    std::string severity;
};

struct Rule {
    std::string name;
    std::string field;
    std::string op;
    std::string value;
};

struct Alert {
    std::string name;
    std::string message;
    std::string severity;
};

bool evaluate(const Event &e, const Rule &r);
Alert generateAlert(const Event &e, const Rule &r);