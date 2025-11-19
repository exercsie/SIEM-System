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
}