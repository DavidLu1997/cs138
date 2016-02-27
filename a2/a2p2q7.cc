#include <iostream>
#include <string>
using namespace std;

void printReverseRecursive() {
    string n;
    cin >> n;

    if(cin.eof()) {
        return;
    }

    printReverseRecursive();

    cout << n << endl;
}
