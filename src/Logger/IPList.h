#pragma once
#include <string>
#include <fstream>
#include <iostream>

struct IPNode {
    std::string ip;
    IPNode *next;

    IPNode(std::string ip) : ip(ip), next(nullptr) {}
};

class IPList {
private:
    IPNode *head;

public:
    IPList() : head(nullptr) {}

    void insert(std::string ip) {
        IPNode *newNode = new IPNode(ip);
        newNode->next = head;
        head = newNode;
    }

    bool loadFromFile(const std::string &filename) {
        std::ifstream file (filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open IP list file: " << filename << "\n";
            return false;
        }

        std::string ip;
        while (std::getline(file, ip)) {
            if (!ip.empty())
                insert(ip);
        }

        return true;
    }

    template<typename Func>
    void forEach(Func func) const {
        IPNode* current = head;
        while (current) {
            func(current->ip);
            current = current->next;
        }
    }

    bool contains(const std::string &ip) const {
        IPNode *current = head;
        while (current) {
            if (current->ip == ip) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void printIPs() const {
        IPNode *current = head;
        int x = 1;
        while (current) {
            std::cout << x++ << " - " << current->ip <<"\n";
            current = current->next;
        }
        if (head == nullptr) {
            std::cout << "No blocked ips\n";
        }
    }

    std::string getIP(int x) const {
        IPNode *current = head;
        int currentx = 1;
        while (current) {
            if (currentx == x) {
                return current->ip;
            }
            current = current->next;
            currentx;
        }
        return "";
    }

    bool remove(const std::string &ip) {
        IPNode *current = head;
        IPNode *previous = nullptr;

        while (current) {
            if (current->ip == ip) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    bool saveAllToFile(const std::string &filename) const {
        std::ofstream file(filename, std::ios::trunc);
        if (!file.is_open()) {
            return false;
        }
        IPNode *current = head;
        while (current) {
            file << current->ip << "\n";
            current = current->next;
        }
        return true;
    }

    bool saveToFile (const std::string &filename) const {
        std::ofstream file (filename, std::ios::app);
        if (!file.is_open()) return false;

        file << head->ip << "\n";
        return true;
    }

    ~IPList() {
        IPNode *current = head;
        while (current) {
            IPNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
};