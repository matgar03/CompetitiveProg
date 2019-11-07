#include <iostream>
#include <cstring>

using namespace std;

#define MAX_N 10
#define MAX_JUGADORES (1 << MAX_N)

bool v[MAX_JUGADORES];

int n, m;

int cuantos(int ini, int fin, bool & rival) {
	if (fin - ini == 1) {
		rival = v[ini] || v[fin];
		if ((v[ini] && !v[fin]) || (!v[ini] && v[fin]))return 1;
		return 0;
	}
	bool r1, r2;
	int sol = cuantos(ini, (ini + fin) / 2, r1) + cuantos((ini + fin ) / 2 + 1, fin, r2);
	rival = r1 || r2;
	if ((r1 && !r2) || (!r1 && r2)) ++sol;
	return sol;
}

int solucion() {
	int sol;
	cin >> n >> m;
	memset(v, 1, sizeof(v));

	for (int i = 0; i < m; ++i) {
		int p;
		cin >> p;
		v[p - 1] = false;
	}

	bool aux;
	return cuantos(0,(1 << n)-1,aux);
}

int main() {
	int nc;
	cin >> nc;
	for (int i = 0; i < nc; ++i) {
		cout << solucion()<<'\n';
	}
	return 0;
}