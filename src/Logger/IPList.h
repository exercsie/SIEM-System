#include <string>

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

    ~IPList() {
        IPNode *current = head;
        while (current) {
            IPNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
};