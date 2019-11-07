#include <iostream>
#include <map>
#include <vector>

using namespace std;
long long int n, m, k ,v;

void resuelve(map<int, vector<long long int>> &mapa) {
	for (int i = 0; i < m; ++i) {
		cin >> k >> v;
		--k;
		if (mapa[v].size() >= k+1) cout << mapa[v][k];
		else cout << 0;
		cout << '\n';
	}
}


int main() {
	
	vector<long long int> aux;
	while (cin >> n >> m) {
		long long int num;
		map<int, vector<long long int>> mapa;
		for (long long int pos = 1; pos <= n; ++pos) {
			cin >> num;
			if (mapa.count(num)) {
				mapa[num].push_back(pos);
			}
			else {
				aux.push_back(pos);
				mapa.insert(make_pair(num, aux));
				aux.pop_back();
			}
		}
		resuelve(mapa);
	}
	return 0;
}