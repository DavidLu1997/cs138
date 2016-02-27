#include <iostream>
#include <string>
using namespace std;
int main() {
    int n;
    cin >> n;
    if(n <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }
    string str;
    getline(cin, str);
    while(getline(cin, str)) {
        if(str.length() > n) {
            cout << str.substr(0, n);
        }
        else {
            cout << str;
        }
        cout << endl;
    }
    return 0;
}
