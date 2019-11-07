#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <map>

using namespace std;

using vi=vector<int>;
using vvii=vector < vector<pair<int, int>>>;

int n, m,q;
bool enc;

void solucion(vi& costes, vvii& aristas, map<pair<int, int>,int > & mapa) {
	priority_queue<pair<pair<int, int>, int>> q;
	
	int fuel,s, d;
	cin >>fuel>> s >> d;
	q.push({ {0,0},s });
	pair<pair<int, int>, int> aux;
	while (!q.empty() && !enc) {

		aux = q.top(); q.pop();
		if (!mapa.count({ aux.first.second,aux.second })||mapa[{ aux.first.second, aux.second }]<aux.first.first) {
			
			mapa[{ aux.first.second, aux.second }] = aux.first.first;
			if (aux.second == d)enc = true;
			else {
				for (unsigned int i = 0; i < aristas[aux.second].size(); ++i) {
					if (aristas[aux.second][i].first <= -aux.first.second) {
						q.push({ {aux.first.first,aux.first.second + aristas[aux.second][i].first},aristas[aux.second][i].second });
					}
				}
				if (-aux.first.second < fuel)q.push({ {aux.first.first - costes[aux.second],aux.first.second - 1},aux.second });
			}
		}
	}

	if (enc)cout << -aux.first.first << '\n';
	else cout << "impossible\n";
}


int main() {
	while (cin >> n >> m) {
		vi costes(n);
		vvii aristas(n);
		
		for (int i = 0; i < n; ++i) {
			cin >> costes[i];
		}
		int a1, a2, a3;
		for (int i = 0; i < m; ++i) {
			cin >> a1 >> a2 >> a3;
			aristas[a1].push_back({ a3,a2 });
			aristas[a2].push_back({ a3,a1 });
		}
		cin >> q;
		while (q--) {
			enc = false;
			map<pair<int, int>, int > mapa;
			solucion(costes, aristas,mapa);
		}
	}
	return 0;
}