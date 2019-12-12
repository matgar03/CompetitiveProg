#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <queue>
#include <algorithm>


using namespace std;
int cont, n, V, A, Q, src, dest;

int  numSets;
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

//using viii = vector<pair<int, pair<int, int>>>;
using vvii = vector<vector<pair<int, int>>>;


void solucion(vvii& aristas) {
	cin >> Q;
	bool enc;
	int sol;
	for (int i = 0; i < Q; ++i) {
		cin >> src >> dest;
		enc = false;
		--src; --dest;
		sol = 0;
		unordered_map<int, int> mapa;
		priority_queue<pair<int, int>> q;
		q.push({ 0,src });
		pair<int, int> aux;
		while (!q.empty() && !enc) {
			aux = q.top(); q.pop();
			if (!mapa.count(aux.second)) {
				mapa[aux.second] = 1;
				if (aux.first < sol)sol = aux.first;
				if (aux.second == dest)enc = true;
				else {
					for (int i = 0; i < aristas[aux.second].size(); ++i) {
						q.push({ -aristas[aux.second][i].second,aristas[aux.second][i].first });
					}
				}

			}

		}
		if (enc)cout << -sol << '\n';
	}
	cout << '\n';
}




int main() {
	cont = 1; cin >> n;
	while (n--) {
		cin >> V >> A;
		int a1, a2, a3;
		vector<pair<int, pair<int, int>>> aristas;
		vvii aristas2(V);
		for (int i = 0; i < A; ++i) {
			cin >> a1 >> a2 >> a3;
			--a1; --a2;
			aristas.push_back({ a3,{a1,a2} });
			/*aristas[a1].push_back({ a2,a3 });
			aristas[a2].push_back({ a1,a3 });*/
		}

		init(V);
		sort(aristas.begin(), aristas.end());
		double coste = 0;
		for (auto ar : aristas) {
			if (find(ar.second.first) != find(ar.second.second)) {
				merge(ar.second.first, ar.second.second);
				aristas2[ar.second.first].push_back({ ar.second.second,ar.first });
				aristas2[ar.second.second].push_back({ ar.second.first,ar.first });
			}
			if (numSets == 1) break;
		}
		cout << "Case " << cont << '\n';
		solucion(aristas2);

		++cont;
	}
	return 0;
}
