#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <iomanip>
using namespace std;
int n; int cont;

using vvi= vector<vector<int>>;

void bfs(int s, int t, const vvi& adj, const vvi& cap, vector <int>& parent, vector<bool>& visited) {
	queue<int> q;
	q.push(s);
	parent[s] = -1; visited[s] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == t) break;
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i];
			if (!visited[v] && (cap[u][v] > 0)) {
				parent[v] = u;
				visited[v] = true;
				q.push(v);
			}
		}
	}
}

void solucion() {
	vector<vector<int>> adj(n);
	bool enc;
	vector<vector<int>> cap(n, vector<int>(n, 0));
	int s, t, c;
	cin >> s >> t >> c;
	--s;
	--t;
	for (int i = 0; i < c; ++i) {
		int a1, a2, a3;
		cin >> a1 >> a2 >> a3;

		a1--;
		a2--;
		/*
		if (a1 == s) {
			adj[a1].push_back(a2);
			cap[a1][a2] = a3;

		}
		else if (a1 == t) {
			adj[a2].push_back(a1);
			cap[a2][a1] = a3;
		}
		else if (a2 == s) {
			adj[a2].push_back(a1);
			cap[a2][a1] = a3;
		}
		else if (a2 == t) {
			adj[a1].push_back(a2);
			cap[a1][a2] = a3;
		}
		*/
		//else {
		enc = false;
		for (int i = 0; i < adj[a1].size() && !enc; ++i) {
			if (adj[a1][i] == a2) {
				enc = true;
				cap[a1][a2] += a3;
				cap[a2][a1] += a3;
			}
		}
		if (!enc) {
			adj[a1].push_back(a2);
			adj[a2].push_back(a1);
			cap[a1][a2] = a3;
			cap[a2][a1] = a3;
		}


		//}
	}

	cout << "Network " << cont << '\n';
	int ret = 0;
	int sol;
	do
	{
		vector<int>parent(n);
		vector<bool> visited(n, false);
		sol = INT_MAX;
		bfs(s, t, adj, cap, parent, visited);
		if (!visited[t])sol = 0;
		else {
			int v = t;
			while (v != s) {
				sol = min(cap[parent[v]][v], sol);
				v = parent[v];
			}
			v = t;
			while (v != s) {
				cap[parent[v]][v] -= sol;
				cap[v][parent[v]] += sol;
				v = parent[v];
			}
		}
		ret += sol;
	} while (sol > 0);
	cout << "The bandwidth is " << ret << ".\n\n";
}

int main() {
	cin >> n;
	cont = 1;
	while (n != 0) {
		solucion();
		cin >> n;
		++cont;
	}
	return 0;
}
