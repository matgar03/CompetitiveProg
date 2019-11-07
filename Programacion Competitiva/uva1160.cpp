#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
using arista = pair<int, pair<int, int>>;

vector<int> C; int numSets;
void init(int n) {
	C.assign(n, 0); numSets = n;
	for (int i = 0; i < n; ++i) C[i] = i;
}
int find(int x) {
	return (C[x] == x) ? x : C[x] = find(C[x]);
}
void merge(int x, int y) {
	C[find(x)] = find(y);
	--numSets;
}


int main() {
	int a, b,aris,vert;
	while (cin >> a) {
		vector<arista> aristas;
		unordered_map<int, int> mapa;
		vert = 0; aris = 0;
		while (a != -1) {
			if (!mapa.count(a)) {
				mapa[a] = vert;
				++vert;
			}
			cin >> b;
			if (!mapa.count(b)) {
				mapa[b] = vert;
				++vert;
			}
			++aris;
			aristas.push_back({ 1,{mapa[a],mapa[b]} });
			cin >> a;
		}
		sort(aristas.begin(), aristas.end());
		init(vert);
		int coste = 0;
		for (auto ar : aristas) {
			if (find(ar.second.first) != find(ar.second.second)) {
				merge(ar.second.first, ar.second.second);
				coste++;
			}
			if (numSets == 1) break;
		}
		cout << aris-coste << '\n';
	}
	return 0;
}