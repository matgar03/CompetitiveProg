#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>

using namespace std;

int n,c;

void dijkstra(int s, vector<int> & dist,const vector<vector<pair<int, int>>> &v, vector<int>& ant) {
	dist[s] = 0;
	
	priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, s });
	while (!pq.empty()) {
		pair<int, int> front = pq.top(); pq.pop();
		int d = front.first, u = front.second;
		if (d > dist[u]) continue;
		for (auto a : v[u]) {
			if (dist[u] + a.first < dist[a.second]) {
				dist[a.second] = dist[u] + a.first;
				ant[a.second] = u;
				pq.push({ dist[a.second], a.second });
			}		}	}}

void solucion() {
	vector<vector<pair<int,int>>> v(n);
	int tam,ini,fin;
	for (int i = 0; i < n; ++i) {
		cin >> tam;
		vector<pair<int, int>> aux(tam);
		for (int j = 0; j < tam; ++j) {
			cin >> aux[j].second >> aux[j].first;
			--aux[j].second;
		}
		v[i] = aux;
	}
	vector<int> ant(n);
	vector<int> dist(n, INT_MAX);
	cin >> ini >> fin;
	--ini; --fin;
	dijkstra(ini, dist,v,ant);
	vector<int> sol;
	sol.push_back(fin);
	while (sol[sol.size()-1] != ini) {
		sol.push_back(ant[sol[sol.size() - 1]]);
	}
	cout << "Case " << c << ": Path =";
	for (int i = sol.size() - 1; i >= 0; --i) {
		cout << ' ' << sol[i] + 1;
	}
	cout << "; " << dist[fin] << " second delay\n";
}



int main() {
	cin >> n;
	c = 0;
	while (n != 0) {
		++c;
		solucion();
		cin >> n;
	}
	return 0;
}