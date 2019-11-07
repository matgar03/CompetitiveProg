#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;
using ss = pair<string, string>;
using vvi= vector<vector<int>>;

vector<int> match, vis;

int aug(int l, const vvi& m) {
	if (vis[l]) return 0;
	vis[l] = 1;
	for (auto r : m[l]) {
		if (match[r] == -1 || aug(match[r], m)) {
			match[r] = l;
			return 1;
		}
	}
	return 0;
}

void solucion() {

	int c, d, v;
	cin >> c >> d >> v;
	vector<ss> gato;
	vector <ss> perro;
	for (int i = 0; i < v; ++i) {

		string s1, s2;
		cin >> s1 >> s2;
		if (s1[0] == 'C') {
			gato.push_back(ss(s1, s2));
		}
		else perro.push_back(ss(s1, s2));
	}
	sort(gato.begin(), gato.end());
	sort(perro.begin(), perro.end());
	vector<vector <int>> adj(gato.size());
	for (int i = 0; i < gato.size(); ++i) {
		for (int j = 0; j < perro.size(); ++j) {
			if (perro[j].first == gato[i].second && perro[j].second == gato[i].first) {
				adj[i].push_back(j);
			}
			else if (perro[j].first > gato[i].second || perro[j].second > gato[i].first)break;
		}
	}
	int mcbm = 0;
	match.assign(gato.size() + perro.size(), -1);
	for (int l = 0; l < gato.size(); l++) {
		vis.assign(gato.size(), 0);
		mcbm += aug(l, adj);
	}
	cout << gato.size() + perro.size()-mcbm << '\n';

}



int main() {
	int n;
	cin >> n;
	while (n--) {
		solucion();
	}
	return 0;
}