#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define RR 1
#define RL 2
#define C 3
#define J 4
#define F 5
#define R 6

vector<string> raw;
vector<string> original;
vector< vector<int> > indexOriginal;
vector<string> justified;
int just = RR;
int mode = F;
int n;

void process();
void justify();
void print();
void printK(int k);
void printS(string s);

string rr(string s);
string rl(string s);
string c(string s);
string j(string s);

int main() {
    string filename;

    cin >> n >> filename;

    if(n <= 0) {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    ifstream in (filename.c_str(), ios::in);

    if(!in.is_open()) {
        cerr << "Error, can't open specified text file." << endl;
        return 1;
    }

    string temp1, temp2;
    int temp;

    while(in >> temp1) {
        raw.push_back(temp1);
    }
    in.close();

    process();

    while(cin >> temp1) {

        if(temp1 == "rr") {
            just = RR;
        }
        else if(temp1 == "rl") {
            just = RL;
        }
        else if(temp1 == "c") {
            just = C;
        }
        else if(temp1 == "j") {
            just = J;
        }
        else if(temp1 == "f") {
            mode = F;
        }
        else if(temp1 == "r") {
            mode = R;
        }
        else if(temp1 == "p") {
            print();
        }
        else if(temp1 == "k") {
            cin >> temp;
            printK(temp);
        }
        else if(temp1 == "s") {
            cin >> temp2;
            printS(temp2);
        }
        else if(temp1 == "q") {
            return 0;
        }
        else {
            cerr << "Error, command is illegal." << endl;
            return 1;
        }
    }

    return 0;
}

void process() {
    string out = "";
    vector<int> t;
    int c = 0;
    for(int i = 0; i < raw.size(); i++) {
        if(out.length() + raw[i].length() + 1 <= n) {
            t.push_back(i);
            out = out + raw[i];
            if(i + 1 != raw.size()) {
                out = out + " ";
            }
            c++;
        }
        else if(out.length() + raw[i].length() == n && c > 0) {
            t.push_back(i);
            out = out + raw[i];
            c++;
            original.push_back(out);
            indexOriginal.push_back(t);
            t.clear();
            out = "";
            c = 0;
        }
        else if(out.length() + raw[i].length() + 1 > n && c == 0) {
            t.push_back(i);
            original.push_back(raw[i].substr(0, n));
            indexOriginal.push_back(t);
            t.clear();
            out = "";
        }
        else if(out.length() + raw[i].length() + 1 > n && c >= 1) {
            out.erase(out.length() - 1, out.length());
            original.push_back(out);
            indexOriginal.push_back(t);
            t.clear();
            out = "";
            c = 0;
            i--;
        }
    }

    if(out.length() > 0) {
        original.push_back(out);
    }
}

void justify() {
    justified = original;
    string (*fun)(string);
    switch(just) {
        case RR:
            fun = rr;
            return;
        break;

        case RL:
            fun = rl;
        break;

        case C:
            fun = c;
        break;

        case J:
            fun = j;
        break;
    }

    for(int i = 0; i < justified.size(); i++) {
        justified[i] = fun(justified[i]);
    }
}

void print() {
    justify();
    int start, end, increment;
    switch(mode) {
        case F:
            start = 0;
            end = justified.size();
            increment = 1;
        break;

        case R:
            start = justified.size() - 1;
            end = -1;
            increment = -1;
        break;
    }

    for(int i = start; i != end; i += increment) {
        cout << justified[i] << endl;
    }
}

void printK(int k) {
    justify();
    if(mode == R) {
        k = justified.size() - k - 1;
    }

    if(k >= 0 && k < justified.size()) {
        cout << justified[k] << endl;
    }
}

void printS(string s) {
    justify();
    int start, end, increment;
    switch(mode) {
        case F:
            start = 0;
            end = justified.size();
            increment = 1;
        break;

        case R:
            start = justified.size() - 1;
            end = -1;
            increment = -1;
        break;
    }

    for(int i = start; i != end; i += increment) {
		if (justified[i].find(s) != string::npos) {
			cout << justified[i] << endl;
		}
    }
}

string rr(string s) {
    string temp = s;
    if(temp[temp.length() - 1] == ' ') {
        temp.erase(temp.length() - 1);
    }
    return temp;
}

string rl(string s) {
    string temp = s;

    int si = n - temp.size();

    for(int i = 0; i < si; i++) {
        temp = " " + temp;
    }
    return temp;
}

string j(string s) {
    string temp = s;

    if(temp.find(' ') == string::npos) {

        for(int i = 0; i < n - s.length(); i++) {
            temp = temp + " ";
        }
        return temp;
    }

    int si = 0;
    if(temp.length() < n) {
        si = n - temp.length();
    }
    if(si == 0 && temp[n-1] != ' ') {
        return temp;
    }
    else if(si == 0 && temp[n-1] == ' ') {
        si++;
    }

    bool hole = false;
    int j = 0;
    while(j < si) {
        for(int i = 0; i < temp.length() && j < si; i++) {
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

string c(string s) {
    string temp = s;

    int si = n - temp.size();

    int r = si/2, l = si/2;
    if(si % 2 == 1) {
        r++;
    }

    for(int i = 0; i < r; i++) {
        temp = " " + temp;
    }
    for(int i = 0; i < l; i++) {
        temp = temp + " ";
    }
    return temp;
}

