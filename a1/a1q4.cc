#include <iostream>
#include <vector>
#include <string>
using namespace std;

string format(string &out, int n) {
    string temp = out;

    if(temp.find(' ') == string::npos) {

        for(int i = 0; i < n - out.length(); i++) {
            temp = temp + " ";
        }
    }
    else {
        int s = 0;
        if(temp.length() < n) {
            s = n - temp.length();
        }
        if(s == 0 && temp[n-1] != ' ') {
            return temp;
        }
        else if(s == 0 && temp[n-1] == ' ') {
            s++;
        }

        bool hole = false;
        int j = 0;
        while(j < s) {
            for(int i = 0; i < temp.length() && j < s; i++) {
                if(temp[i] == ' ' && !hole) {
                    temp.insert(i, " ");
                    j++;
                    hole = true;
                    continue;
                }
                if(temp[i] != ' ') {
                    hole = false;
                }
            }
        }
    }
    return temp;
}


int main() {
    int n;
    cin >> n;

    if(n <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    vector<string> s;
    string str;
    while(!cin.eof()) {
        cin >> str;
        s.push_back(str);
    }
    s.erase(s.end());

    string out = "";
    int c = 0;
    for(int i = 0; i < s.size(); i++) {
        if(out.length() + s[i].length() + 1 <= n) {
            out = out + s[i];
            if(i + 1 != s.size()) {
                out = out + " ";
            }
            c++;
        }
        else if(out.length() + s[i].length() == n && c > 0) {
            out = out + s[i];
            c++;
            cout << format(out, n) << endl;
            out = "";
            c = 0;
        }
        else if(out.length() + s[i].length() + 1 > n && c == 0) {
            cout << s[i].substr(0, n) << endl;
            out = "";
        }
        else if(out.length() + s[i].length() + 1 > n && c >= 1) {
            out.erase(out.length() - 1, out.length());
            cout << format(out, n) << endl;
            out = "";
            c = 0;
            i--;
        }
    }

    if(out.length() > 0) {
        cout << format(out, n) << endl;
    }
    return 0;
}

