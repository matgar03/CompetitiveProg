#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

void solucion() {
	int dist;
	cin >> dist;
	dist = dist / 100;
	vector<vector<int>> m(10, vector<int>(dist));
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < dist; ++j) {
			cin >> m[9-i][j];
		}
	}

	vector<vector<int>> sol(10, vector<int>(dist+1,-1));
	sol[0][0] = 0;
	for (int j = 1; j < dist; ++j) {
		for (int i = 0; i <= j && i <10; ++i) {
			int mini=INT_MAX;
			if (i < 9 && sol[i + 1][j - 1] != -1) {
				mini = min(mini, 20 - m[i + 1][j - 1] + sol[i + 1][j - 1]);
			}
			if (sol[i][j - 1] != -1) {
				mini = min(mini, 30 - m[i][j - 1] + sol[i][j - 1]);
			}
			if (i>0 && sol[i - 1][j - 1] != -1) {
				mini = min(mini, 60 - m[i - 1][j - 1] + sol[i -1][j - 1]);
			}
			sol[i][j] = mini;
		}
	}
	int res = min(sol[0][dist - 1] + 30 - m[0][dist - 1], sol[1][dist - 1] + 20 - m[1][dist - 1]);
	cout << res << "\n\n";
}

int main() {
	int ncasos;
	cin >> ncasos;
	while (ncasos--) {
		solucion();
	}
	return 0;
}