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

int N, M;
vi  match, vis;
vi res;

int aug(int l, const vvi& adj) {
	if (vis[l])return 0;
	vis[l] = 1;
	for (int r : adj[l]) {
		if (match[r] == -1 || aug(match[r], adj)) {
			match[r] = l;
			return 1;
		}
	}
	return 0;
}

bool bien(const vector<char>& b, const vector <char>& a){
	int j = 0;
	for (int i = 0; i < a.size(); ++i) {
		bool found = false;
		while (!found && j < b.size()) {
			if (a[i] == b[j]) {
				found = true;
				++j;
			}
			else if (b[j] > a[i])return false;
			else ++j;
		}
		if(!found && j >= b.size())return false;
	}
	return true;
}

void solucion() {
	vector<vector<char>> voc(N);
	vector<vector<char>> chal(M);
	char c;
	for (int i = 0; i < N; ++i) {
		cin.get(c);
		while (c != '\n') {
			voc[i].push_back(c);
			cin.get(c);
		}
		sort(voc[i].begin(), voc[i].end());
	}

	for (int i = 0; i < M; ++i) {
		cin.get(c);
		while (c != '\n') {
			chal[i].push_back(c);
			cin.get(c);
		}
		sort(chal[i].begin(), chal[i].end());
	}
	vvi adj(N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (bien(voc[i], chal[j]))adj[i].push_back(j);
		}
	}
	match.assign(N + M, -1);
	vis.assign(N, 0); int sol = 0;
	for (int i = 0; i < N; ++i) {
		vis.assign(N, 0);
		sol += aug(i, adj);
	}
	cout << sol << '\n';
}

int main() {
	while (cin >> N >> M) {
		char aux;
		cin.get(aux);
		solucion();
		
	}

	

	return 0;
}
