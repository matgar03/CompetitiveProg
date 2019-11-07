#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int F, C;

int df[] = { 0,1,1,1,0,-1,-1,-1 }, dc[] = { 1,1,0,-1,-1,-1,0,1 };

int cf[] = { -2,-2,-1,1,2,2,-1,1 }, cc[] = { -1,1,2,2,-1,1,-2,-2 };

bool ok(int i, int j) {
	return 0 <= i && i < F && 0 <= j && j < C;
}



void marcar(int i, int j, vector<vector<char>>& m) {
	int ni, nj;
	m[i][j] = 'Z';
	for (int k = 0; k < 8; ++k) {
		ni = i + cf[k]; nj = j + cc[k];
		if (ok(ni,nj)) m[ni][nj]='Z';
	}

}

void solucion() {
	cin >> F >> C;
	char aux;
	cin.get(aux);
	pair<int,int> ori, fin;
	vector<vector<char>> m(F, vector<char>(C));
	vector<vector<int>> dist(F, vector<int>(C));
	for (int i = 0; i < F; ++i) {
		for (int j = 0; j < C; ++j) {
			cin.get(aux);
			if (aux == 'A')ori = pair<int, int>(i, j);
			else if (aux == 'B')fin = pair<int, int>(i, j);
			else if (aux == 'Z')marcar(i, j, m);
		}
		cin.get(aux);
	}
	m[fin.first][fin.second] = 'B';
	m[ori.first][ori.second] = 'Z';

	
	
	queue<pair<int, int>> q;
	dist[ori.first][ori.second] = 0;
	q.push(ori);
	int ni, nj;
	bool final = false;
	while (!q.empty() && !final) {
		pair<int,int> v = q.front(); q.pop();
		for (int w = 0; w < 8; ++w) {
			ni = v.first + df[w]; nj = v.second + dc[w];
			if (ni == fin.first && nj == fin.second) {
				dist[ni][nj] = dist[v.first][v.second] + 1;
				final = true;
			}
			else if (ok(ni,nj) && m[ni][nj]!='Z') {
				dist[ni][nj] = dist[v.first][v.second] + 1;
				m[ni][nj] = 'Z';
				q.push(pair<int,int>(ni,nj));
			}
			
		}
	}
	

	if (final) cout << "Minimal possible length of a trip is " << dist[fin.first][fin.second] << '\n';
	else cout << "King Peter, you can't go now!\n";	

}
int main() {
	int casos;
	cin >> casos;
	while (casos--) {
		solucion();
	}
	return 0;
}