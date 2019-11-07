#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <iomanip>
using namespace std;
int n,m;

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
	int s, t;
	s = 0;
	t = 1;
	for (int i = 0; i < m; ++i) {
		int a1, a2, a3;
		cin >> a1 >> a2 >> a3;
		a1--;
		a2--;		
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
	}

	int ret = 0;
	int sol;
	vector<bool> vis(n);
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
		vis = visited;
		ret += sol;
	} while (sol > 0);
	vector<pair<int, int>> soluc;
	for (int i = 0; i < n; ++i) {
		if (vis[i]) {
			for (int j = 0; j < adj[i].size(); ++j) {
				if (!vis[adj[i][j]])soluc.push_back({ i+1, 1+adj[i][j] });
			}
		}
	}
	sort(soluc.begin(), soluc.end());
	for (int i = 0; i < soluc.size(); ++i) {
		cout << soluc[i].first << ' ' << soluc[i].second << '\n';
	}
	cout << '\n';
}

int main() {
	cin >> n >>m;
	while (n != 0 || m!=0) {
		if (n > 1)solucion();
		else cout << '\n';
		cin >> n >>m;
	}
	return 0;
}