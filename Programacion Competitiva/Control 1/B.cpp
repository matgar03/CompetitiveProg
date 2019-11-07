#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <iomanip>
#include <climits>
#include <algorithm>
#include <functional>
#include <cmath>

using namespace std;

using vi=vector<int>;
using vvi=vector<vi>;
using ii=pair<int, int>;
using iiii=pair<ii, ii>;
using vii =vector<ii>;
using vvii=vector<vii>;

int n,g;


int main() {
	int s, r,cont;
	while (cin >> n >> g) {
		vi dif;
		cont = 0;
		for (int i = 0; i < n;++i) {
			cin >> s >> r;
			if (s - r <= 0) {
				dif.push_back(s - r);
			}
			else cont += 3;
		}
		sort(dif.begin(), dif.end());
		int i = dif.size() - 1;
		while (g > 0 && i >= 0) {
			++dif[i];
			if (dif[i] > 0)--i;
			--g;
		}
		for (int i = 0; i < dif.size(); ++i) {
			if (dif[i] == 0)++cont;
			else if (dif[i] > 0)cont += 3;
		}
		cout << cont << '\n';

	}

	return 0;
}