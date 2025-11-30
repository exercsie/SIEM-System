#pragma once
#include <iostream>
#include <vector>
#include "../Logger/IPList.h"
#include "../Event_Processor/eventProcessor.h"

void menu(IPList &unsafeIPs, IPList &blockedIPs, std::vector<Event> &events, std::vector<Rule> &rules);