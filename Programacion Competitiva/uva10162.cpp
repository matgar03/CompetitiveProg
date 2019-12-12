#include <iostream>
#include <string>
#include <vector>

using namespace std;
string s;
using vi = vector<int>;
using vvi = vector<vector<int>>;

int main() {
	cin >> s;
	vvi vals(9);
	vals[0] = { 1 };
	vals[1] = { 4,6 };
	vals[2] = { 7,3 };
	vals[3] = { 6 };
	vals[4] = { 5 };
	vals[5] = { 6 };
	vals[6] = { 3,7 };
	vals[7] = { 6,4 };
	vals[8] = { 9 };
	//vemos que, cada 10 números, se suma 7;
	vi sumas = { 7,4,1,8,5,2,9,6,3,0 };	
	while (s != "0") {
		int sol = 0;
		if (s.size() > 1 && s[s.size()-2]!=0)sol += sumas[s[s.size() - 2]-'0'-1];
		int k = s[s.size() - 1] - '0';
		for (int i = 1; i <= s[s.size() - 1] - '0';++i) {
			sol += vals[i - 1][0];
		}
		if (s.size() > 1 && (s[s.size()-2]-'0')%2==1) {
			if (s[s.size() - 1] > '1')sol += 2;
			if (s[s.size() - 1] > '2')sol -= 4;
			if (s[s.size() - 1] > '6')sol += 4;
			if (s[s.size() - 1] > '7')sol -= 2;
		}
		cout << sol % 10 << '\n';
		cin >> s;
	}
	return 0;
}