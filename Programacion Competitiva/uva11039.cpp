#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N;

int main() {
	cin >> N;
	int pisos,aux, cont;
	bool act, enc;
	while (N--) {
		vector<int> p, n;
		cont = 0;
		cin >> pisos;
		while (pisos--) {
			cin >> aux;
			if (aux > 0) p.push_back(aux);
			else n.push_back(aux);
		}
		sort(p.begin(), p.end());
		sort(n.begin(), n.end());
		int i = p.size() - 1, j = 0;
		if (p.size() == 0 && n.size() == 0)cout << "0\n";
		else if (p.size() == 0 || n.size() == 0)cout << "1\n";
		else {
			if (p[i] > -1 * n[j])aux = true;
			else aux = false;
			++cont;
			while (i >= 0 && j < n.size()) {
				enc = false;
				if (aux) {
					while (j < n.size() && !enc) {
						if (-1 * n[j] < p[i]) {
							enc = true;
						}
						else ++j;
					}
					--i;
				}
				else {
					while (i >= 0 && !enc) {
						if (p[i] < -1 * n[j]) {
							enc = true;
						}
						else --i;
					}
					++j;
				}
				if (enc) ++cont;
				aux = !aux;
			}
			cout << cont << '\n';
		}
	}

	return 0;
}