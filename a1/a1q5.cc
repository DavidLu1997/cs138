#include <iostream>
#include <vector>
#include <string>
using namespace std;

string rr(string &out, int n);
string j(string &out, int n);
string rl(string &out, int n);
string c(string &out, int n);
void format(vector<string> out, int n, string c1, string c2);

bool fnordSpecial = false;
vector<bool> fnord;
int main() {
    int n;
    cin >> n;

    if(n <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    string c1, c2;
    cin >> c1 >> c2;
    vector<string> s;
    string str;
    while(!cin.eof()) {
        cin >> str;
        s.push_back(str);
    }
    s.erase(s.end());
    cout << c1 << endl;
    if(c1 != "rr" && c1 != "j" && c1 != "rl" && c1 != "c" && c2 != "f" && c2 != "r" && c2 != "g") {
        cerr << "Error, command is illegal." << endl;
        return 1;
    }
    string out = "";
    vector<string> output;
    int c = 0;
    for(int i = 0; i < s.size(); i++) {
        if(out.length() + s[i].length() + 1 <= n) {
            if(s[i].find("fnord") != string::npos) {
            fnordSpecial = true;
        }
            out = out + s[i];
            if(i + 1 != s.size()) {
                out = out + " ";
            }
            c++;
        }
        else if(out.length() + s[i].length() == n && c > 0) {
            if(s[i].find("fnord") != string::npos) {
            fnordSpecial = true;
        }
            out = out + s[i];
            c++;
            output.push_back(out);
            fnord.push_back(fnordSpecial);
            fnordSpecial = false;
            out = "";
            c = 0;
        }
        else if(out.length() + s[i].length() + 1 > n && c == 0) {
            if(s[i].find("fnord") != string::npos) {
            fnordSpecial = true;
        }
            output.push_back(s[i].substr(0, n));
            fnord.push_back(fnordSpecial);
            fnordSpecial = false;
            out = "";
        }
        else if(out.length() + s[i].length() + 1 > n && c >= 1) {
            out.erase(out.length() - 1, out.length());
            output.push_back(out);
            fnord.push_back(fnordSpecial);
            fnordSpecial = false;
            out = "";
            c = 0;
            i--;
        }
    }

    if(out.length() > 0) {
            output.push_back(out);
            fnord.push_back(fnordSpecial);
            fnordSpecial = false;
    }

    format(output, n, c1, c2);

    return 0;
}

string rr(string &out, int n) {
    string temp = out;
    if(temp[temp.length() - 1] == ' ') {
        temp.erase(temp.length() - 1);
    }
    out = "";
    return temp;
}

string j(string &out, int n) {
    string temp = out;

    if(temp.find(' ') == string::npos) {

        for(int i = 0; i < n - out.length(); i++) {
            temp = temp + " ";
        }
        return temp;
    }

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
    return temp;
}

string rl(string &out, int n) {
    string temp = out;

    int s = n - temp.size();

    for(int i = 0; i < s; i++) {
        temp = " " + temp;
    }
    out = "";
    return temp;
}

string c(string &out, int n) {
    string temp = out;

    int s = n - temp.size();

    int r = s/2, l = s/2;
    if(s % 2 == 1) {
        r++;
    }

    for(int i = 0; i < r; i++) {
        temp = " " + temp;
    }
    for(int i = 0; i < l; i++) {
        temp = temp + " ";
    }

    out = "";
    return temp;
}

void format(vector<string> out, int n, string c1, string c2) {

    for(int i = 0; i < out.size(); i++) {
        if(c1 == "rr") {
            out[i] = rr(out[i], n);
        }
        else if(c1 == "j") {
            out[i] = j(out[i], n);
        }
        else if(c1 == "rl") {
            out[i] = rl(out[i], n);
        }
        else if(c1 == "c") {
            out[i] = c(out[i], n);
        }
    }

    switch(c2[0]) {
        case 'f':
            for(int i = 0; i < out.size(); i++) {
                cout << out[i] << endl;
            }
        break;
        case 'r':
            for(int i = out.size() - 1; i >= 0; i--) {
                cout << out[i] << endl;
            }
        break;
        case 'g':
            for(int i = 0; i < out.size(); i++) {
                if(fnord[i]) {
                    cout << out[i] << endl;
                }
            }
        break;
    }
}
