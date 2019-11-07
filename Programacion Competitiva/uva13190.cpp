#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct med {
	string nom;
	int freq;
};

bool operator <(const pair<pair<int, int>, med>& m1, const pair<pair<int, int>, med>& m2) {
	if (m1.first.first == m2.first.first) return m2.first.second < m1.first.second;
	return m2.first.first < m1.first.first;
}

void solucion() {
	int n, m;
	cin >> n >> m;
	med medics;
	priority_queue<pair<pair<int, int>, med>> pq;
	for (int i = 1; i <= n; ++i) {
		cin >> medics.nom >> medics.freq;
		pq.push({{medics.freq, i}, medics});
	}
	for (int i = 0; i < m; ++i) {
		medics = pq.top().second;
		cout << pq.top().first.first << ' ' << medics.nom << '\n';
		pq.push({ {pq.top().first.first + medics.freq,pq.top().first.second}, medics });
		pq.pop();
	}
}

int main() {
	int casos;
	cin >> casos;
	while (casos--) {
		solucion();
	}
	return 0;
}