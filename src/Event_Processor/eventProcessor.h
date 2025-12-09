#pragma once
#include <vector>
#include "../Logger/IPList.h"
#include "../Logger/logger.h"

int processEvents(const std::vector<Event> &events, const std::vector<Rule> &rules, const IPList &unsafeIPs);