#include <iostream>
#include <string>
using namespace std;

struct Node {
    string val;
    Node* next;
};

Node* makeList() {
    string n;
    cin >> n;
    if(n.empty()) {
        return NULL;
    }

    Node* start;
    Node* current = new Node;
    start = current;
    current->val = n;

    while(cin >> n) {
        current->next = new Node;
        current = current->next;
        current->val = n;
    }
    current->next = NULL;

    return start;
}
