#pragma once
#include <iostream>
#include <vector>
#include "../Logger/IPList.h"
#include "../eventProcessor/eventProcessor.h"

void menu(IPList &unsafeIPs, IPList &blockedIPs, std::vector<Event> &events, std::vector<Rule> &rules);