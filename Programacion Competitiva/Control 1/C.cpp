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

int h1, m1, h2, m2;

int main() {

	cin >> h1 >> m1 >> h2 >> m2;
	int sol;
	while (h1 != 0 || m1 != 0 || h2 != 0 || m2 != 0) {
		if (h1 == h2 && m1 > m2) {
			sol = 24 * 60 - (m1 - m2);
		}
		else {
			if (h2 < h1) h2 += 24;
			sol = (h2 - h1) * 60;
			sol += m2 - m1;
		}
		cout << sol << '\n';
		cin >> h1 >> m1 >> h2 >> m2;
	}



	return 0;
}
