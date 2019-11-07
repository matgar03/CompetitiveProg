#include <iostream>
#include <vector>
#include <algorithm>;

using namespace std;
int n, m;

void resuelve() {
	vector <int> d(n);
	vector <int> k(m);
	for (int i = 0; i < n; ++i) {
		cin >> d[i];
	}
	for (int i = 0; i < m; ++i) {
		cin >> k[i];
	}
	sort(d.begin(), d.end());
	sort(k.begin(), k.end());
	int sol = 0; int cont = 0;
	for (int j = 0; j < m; ++j) {
		if (k[j] >= d[cont]) {
			sol += k[j];
			++cont;
			if (cont == n) break;
		}		
	}
	if (cont != n) cout << "Loowater is doomed!\n";
	else cout << sol << '\n';

}

int main() {
	cin >> n >> m;
	while (n != 0 || m != 0) {
		resuelve();
		cin >> n >> m;
	}
	return 0;
}