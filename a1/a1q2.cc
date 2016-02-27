#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    if(n <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }
    char c;
    cin >> c;
    vector<string> str_v;
    string str;
    getline(cin, str);
    while(getline(cin, str)) {
        str_v.push_back(str);
    }
    switch(c) {
    case 'f':
        for(int i = 0; i < str_v.size(); i++) {
            if(str_v[i].length() > n) {
                cout << str_v[i].substr(0, n) << endl;
            }
            else {
                cout << str_v[i] << endl;
            }
        }
        break;
    case 'r':
        for(int i = str_v.size() - 1; i >= 0; i--) {
            if(str_v[i].length() > n) {
                cout << str_v[i].substr(0, n) << endl;
            }
            else {
                cout << str_v[i] << endl;
            }
        }
        break;
    case 'g':
        for(int i = 0; i < str_v.size(); i++) {
            if(str_v[i].find("fnord") != string::npos) {
                if(str_v[i].length() > n) {
                    cout << str_v[i].substr(0, n) << endl;
                }
                else {
                    cout << str_v[i] << endl;
                }
            }
        }
        break;
    default:
        cerr << "Error, command is illegal." << endl;
    }
    return 0;
}
