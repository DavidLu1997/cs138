#include <string>
#include <cctype>
using namespace std;

const int val[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int scrabbleValue(string s) {
	int v = 0;
	for (size_t i = 0; i < s.length(); i++) {
		if (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'z') {
			v += val[s[i] - 'a'];
		}
	}
	return v;
}

int scrabbleValue(char c) {
	if (tolower(c) >= 'a' && tolower(c) <= 'z') {
		return val[c - 'a'];
	}
	return 0;
}