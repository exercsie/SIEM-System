#include "logger.h"
#include <iostream>

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
    a.message = "Alert: " + r.name + " User: " + e.username + " IP: " + e.src_ip;
    return a;
}