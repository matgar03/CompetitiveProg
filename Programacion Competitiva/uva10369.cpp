#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <queue>
#include <cmath>


using namespace std;

int s,p,numSets;
vector<int> C;
void init(int n) {
	C.assign(n, 0); numSets = n;
	for (int i = 0; i < n; ++i) C[i] = i;
}

int find(int x) {
	return (C[x] == x) ? x : C[x] = find(C[x]);
}
void merge(int x, int y) { // find(x) != find(y)
	C[find(x)] = find(y);
	--numSets;
}

int main() {
	int n;
	cin >> n;
	cout << fixed << setprecision(2);
	for (int i = 0; i < n; ++i) {
		cin >> s >> p;
		vector <pair<int, int>> v(p);
		vector<pair<double, pair<int, int>>> aristas;
		priority_queue < pair<double, pair<int, int>>> sol;
		for (int i = 0; i < p; ++i) {
			cin >> v[i].first >> v[i].second;
			for (int j = 0; j < i; ++j) {
				aristas.push_back({ sqrt(1.0 * (1.0 * v[i].first - v[j].first) * (1.0 * v[i].first - v[j].first) + 1.0 * (1.0 * v[i].second - v[j].second) * (1.0 * v[i].second - v[j].second)),{j,i} });
			}
		}
		init(p);
		sort(aristas.begin(), aristas.end());
		double coste = 0;
		for (auto ar : aristas) {
			if (find(ar.second.first) != find(ar.second.second)) {
				merge(ar.second.first, ar.second.second);
				sol.push(ar);
				if (ar.first > coste)coste = ar.first;
			}
			if (numSets == 1) break;
		}
		vector<bool> marked(p,false);
		cout << '\n';
		while (!sol.empty() && s > 1 /*&& !enc*/) {
			sol.pop(); --s;
			/*if (!marked[sol.top().second.first] && !marked[sol.top().second.second] && s > 1) {
				marked[sol.top().second.first] = true;
				marked[sol.top().second.second] = true;
				--s; --s;
				sol.pop();
			}
			else if (!marked[sol.top().second.first] && marked[sol.top().second.second] && s > 0) {
				marked[sol.top().second.first] = true;
				--s;
				sol.pop();
			}
			else if (marked[sol.top().second.first] && !marked[sol.top().second.second] && s > 0) {
				marked[sol.top().second.second] = true;
				--s;
				sol.pop();
			}
			else if (marked[sol.top().second.first] && marked[sol.top().second.second]) {
				sol.pop();
			}
			else enc = true;*/
		}
		if (!sol.empty())cout << sol.top().first << '\n';
		else cout << "0.00\n";


	}
	return 0;
}