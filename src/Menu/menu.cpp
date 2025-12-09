#include <iostream>
#include <vector>
#include "menu.h"
#include "../Logger/logger.h"
#include "../Logger/IPList.h"
#include "../Event_Processor/eventProcessor.h"

void menu(IPList &unsafeIPs, IPList &blockedIPs, std::vector<Event> &events, std::vector<Rule> &rules) {
        int choice = -1;

    while (true) {
        std::cout << "\n0 - Exit\n";
        std::cout << "1 - Check alerts \n";
        std::cout << "2 - Block IPs \n";
        std::cout << "3 - Show blocked IPs\n";
        std::cout << "4 - Search user\n";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore (1000, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        } else if (choice > 4) {
            std::cout << "Invalid choice. Try again.\n";
        }

        switch (choice) {
            case 0: std::cout << "\nExiting program.\n";
            return;

            case 1: std::cout << "\nChecking alerts..\n";
            processEvents(events, rules, unsafeIPs);
            break;

            case 2: {
                std::cout << "\nChecking blocked IPs...\n";
                int blockChoice = -1;
                int x = 1;

                while (true) {
                    std::cout << "The current unsafe ips are: \n"; 
                    unsafeIPs.forEach([&](const std::string &unsafeIPs) {
                    std::string user = "Unknown";

                    for (const auto &e : events) {
                        if (e.src_ip == unsafeIPs) {
                            user = e.username;
                            break;
                        }
                    }   
                        
                std::cout << x++ << " - " << unsafeIPs << " User: " << user << "\n";
                });
                    
                    std::vector<Event> selectableIPs;
                    for (const auto &event : events) {
                        if (unsafeIPs.contains(event.src_ip) && !blockedIPs.contains(event.src_ip)) {
                            selectableIPs.push_back(event);
                        }
                    }

                    if (selectableIPs.empty()) {
                        std::cout << "\nThere are no more unsafe IPs to block\n";
                        break;
                    }

                    std::cout << "\n0 - Back to main menu\n";
                    std::cout << "\nWhich IP would you like to block?\n";

                    for (int i = 0; i < selectableIPs.size(); i++) {
                        std::cout << i + 1 << " - " << selectableIPs[i].src_ip << " User: " << selectableIPs[i].username << std::endl;
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

                    std::string ipToBlock = selectableIPs[blockChoice - 1].src_ip;
                    std::string userToBlock = selectableIPs[blockChoice - 1].username;

                    blockedIPs.insert(ipToBlock);
                    blockedIPs.saveToFile("Files/blockedIPs.txt");

                    unsafeIPs.remove(ipToBlock);
                    unsafeIPs.saveAllToFile("Files/unsafeIPList.txt");
                    std::cout << "\nBlocked IP: " << ipToBlock << " User: " << userToBlock << "\n";
                }

                break;
            }

            case 3: std::cout << "\nChecking blocked IPs...\n";
            if (blockedIPs.empty()) {
                std::cout << "There are no blocked ips.\n";
                break;
            }

            int x = 1;

            blockedIPs.forEach([&](const std::string &blockedIPs) {
                std::string user = "Unknown";

                for (const auto &e : events) {
                    if (e.src_ip == blockedIPs) {
                        user = e.username;
                        break;
                    }
                }

                std::cout << x++ << " - " << blockedIPs << " User: " << user << "\n";
            });
            break;

            case 4: std::cout << "\nBringing up search query";
            std::string query;
        }
    }
}