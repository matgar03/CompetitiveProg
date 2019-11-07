#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

float x, y, c;
int tries;

float busqueda(float ini, float fin) {
	float mitad = (ini + fin) / 2;
	float sol = ((sqrt(x * x - mitad * mitad) * sqrt(y * y - mitad * mitad)) / (sqrt(x * x - mitad * mitad) + sqrt(y * y - mitad * mitad))) - c;
	if (abs(sol) < 0.0001  || ++tries == 100)return mitad;
	if (sol > 0)return busqueda(mitad, fin);
	else return busqueda(ini, mitad);
}


void solucion() {
	float sol;
	float fin;
	if (x > y) fin = y;
	else fin = x;
	tries = 0;
	sol = busqueda(0, fin);
	cout  << sol << '\n';
}

int main() {
	cout << fixed << setprecision(3);
	while (cin >> x >> y >> c) {
		solucion();
	}
	return 0;
}