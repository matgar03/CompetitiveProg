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
#include <queue>
#include <set>

using namespace std;

using vi=vector<int>;
using vvi=vector<vi>;
using ii=pair<int, int>;
using iiii=pair<ii, ii>;
using vii =vector<ii>;
using vvii=vector<vii>;

int casos,V,At,Aa,s,d,p;

void solucion(vvii &aviones, vvii & trenes) {
	priority_queue<pair<int, ii>> q;
	map<ii, int> mapa;
	q.push({ 0,{p,s} });
	bool enc = false;
	pair<int, ii> aux;
	while (!q.empty() && !enc) {
		aux = q.top(); q.pop();
		if (!mapa.count(aux.second)) {
			mapa[aux.second] = 1;
			if (aux.second.second == d)enc = true;
			else {
				for (int i = 0; i < trenes[aux.second.second].size(); ++i)
					q.push({ aux.first - trenes[aux.second.second][i].first,{aux.second.first,trenes[aux.second.second][i].second} });
				if (aux.second.first > 0) {
					for (int i = 0; i < aviones[aux.second.second].size(); ++i)
						q.push({ aux.first - aviones[aux.second.second][i].first,{aux.second.first - 1,aviones[aux.second.second][i].second} });

				}
			}

		}
	}
	cout << -aux.first << '\n';

}


int main() {
	cin >> casos;
	while (casos--) {
		cin >> V >> s >> d>>p>>At;
		vvii trenes(V),aviones(V);
		int a1, a2, a3;
		for (int i = 0; i < At; ++i) {
			cin >> a1 >> a2 >> a3;
			trenes[a1].push_back({ a3,a2 });
			trenes[a2].push_back({ a3,a1 });
		}
		cin >> Aa;
		for (int i = 0; i < Aa; ++i) {
			cin >> a1 >> a2 >> a3;
			aviones[a1].push_back({ a3,a2 });
			aviones[a2].push_back({ a3,a1 });
		}
		solucion( aviones,trenes);
	}
	return 0;
}
