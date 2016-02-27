#include <iostream>
#include <string>
using namespace std;

struct Node {
    string val;
    Node* next;
};

void printList (Node *p) {
    while(p != NULL) {
        cout << p->val << endl;
        p = p->next;
    }
}
