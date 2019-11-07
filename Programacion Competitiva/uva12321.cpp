#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int l, g;

void resuelve(vector<pair<int, int>> &gasolineras) {
	int usadas = 1, fin = 0,aux=0;
	bool posible = true;

	sort(gasolineras.begin(), gasolineras.end());
	if (gasolineras[aux].first == 0) {
		while (aux < g && gasolineras[aux].first == 0) { 
			fin = gasolineras[aux].second;
			++aux;
		}
		
		int finaux = fin;
		for (int i = aux; i < g && posible; ++i) {
			if (gasolineras[i].second > finaux && gasolineras[i].first <= fin) {
				finaux = gasolineras[i].second;
			}
			else if (gasolineras[i].first > fin) {
				if (finaux > fin) {
					fin = finaux;
					++usadas;
					--i;
				}
				else posible = false;
			}
		}
		if (fin < l && finaux == l) {
			++usadas;
			fin = l;
		}
	}
	else posible = false;
	if (posible && fin == l)cout << g - usadas << '\n';
	else cout << -1 << '\n';

}

int main() {
	cin >> l >> g;
	int aux1, aux2;
	while (l != 0 || g != 0) {
		vector<pair<int,int>> gasolineras(g);
		for (int i = 0; i < g; ++i) {
			cin >> aux1 >> aux2;
			gasolineras[i].first = max(0, aux1 - aux2);
			gasolineras[i].second = min(l, aux1 + aux2);
		}
		resuelve(gasolineras);
		cin >> l >> g;
	}
	return 0;
}