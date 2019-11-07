#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include <cfloat>
#include <limits>

using namespace std;
double p;
int num;
int caso;

void solucion() {
	vector<pair<int, double>> v(num+1);
	v[0].first = 1;
	v[0].second = p;
	for (int i = 1; i <= num; ++i) {
		cin >> v[i].first >> v[i].second;
	}
	char salto;
	cin.get(salto);
	string aux;
	getline(cin, aux);
	stringstream s(aux);
	vector<int> consultas;
	int k;
	while (s >> k)consultas.push_back(k);
	sort(v.begin(), v.end());
	vector <double> m(201,DBL_MAX );
	m[0] = 0;
	for (int i = 1; i < 201; ++i) {
		for (int j = 0; j < v.size(); ++j) {
			if (v[j].first > i) break;
			if (m[i  - v[j].first] + v[j].second < m[i]) m[i] = m[i - v[j].first] + v[j].second;
		}
	}

	double min = m[200];	
	for (int i = 199; i >= 0; --i) {
		if (m[i] > min) m[i] = min;
		else min = m[i];
	}
	cout << "Case " << caso << ":\n";
	for (int j = 0; j < consultas.size(); ++j) {
		cout << "Buy " << consultas[j] << " for $" << fixed<< setprecision(2) << m[consultas[j]] << '\n';
	}
}

int main() {
	caso = 1;
	while (cin >> p >> num) {
		solucion();
		++caso;
	}

	return 0;
}