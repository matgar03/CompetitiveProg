#include <iostream>
#include <string>

using namespace std;
string s;

int main() {
	int buenos,rotar;
	bool mal;
	while (cin >> s) {
		mal = false;
		buenos  = rotar= 0;
		for (int i = 0; i < s.size()-1; ++i) {
			if (s[i] == '0') {
				++rotar;
				if (s[i + 1] == '0')++buenos;
			}
			else mal = true;
		}
		if (s[s.size() - 1] == '0') {
			++rotar;
			if (s[0] == '0')++buenos;
		}
		else mal = true;
		int aux = s.size();
		if (!mal || !rotar)cout << "EQUAL\n";

		
		else {
			if (buenos*aux > rotar*rotar)cout << "SHOOT\n";
			else if (buenos*aux < rotar*rotar)cout << "ROTATE\n";
			else cout << "EQUAL\n";
		}
	}
	return 0;
}