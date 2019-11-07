#include<iostream>
#include <vector>
#include<climits>
#include<queue>

using namespace std;
int f, c;
pair<int, int> ini, fin;
int df[] = { -1,-1,0,1,1,1,0,-1 }, dc[] = { 0,1,1,1,0,-1,-1,-1 };

bool ok(int i, int j) {
	return (i >= 0 && j >= 0 && i < f && j < c);
}


void resuelve(pair<int, int> ini, const vector<vector<vector<pair<pair<int, int>, int>>>>& aristas){
	vector<vector<int>> dist(f, vector<int>(c));
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j)
			dist[i][j] = INT_MAX;
	}

	deque <pair<int, int>> q;
	dist[ini.first][ini.second] = 0;
	q.push_back(pair<int, int>(ini.first, ini.second));
	bool enc = false;
	while (!q.empty() && !enc)
	{
		pair<int, int> v = q.front();
		q.pop_front();
		if (v.first == fin.first && v.second == fin.second)enc = true;
		else {
			for (int i = 0; i < aristas[v.first][v.second].size(); ++i) {
				if (dist[aristas[v.first][v.second][i].first.first][aristas[v.first][v.second][i].first.second] > dist[v.first][v.second] + aristas[v.first][v.second][i].second) {
					dist[aristas[v.first][v.second][i].first.first][aristas[v.first][v.second][i].first.second] = dist[v.first][v.second] + aristas[v.first][v.second][i].second;
					if (aristas[v.first][v.second][i].second == 0)
						q.push_front(pair<int, int>(aristas[v.first][v.second][i].first.first, aristas[v.first][v.second][i].first.second));
					else
						q.push_back(pair<int, int>(aristas[v.first][v.second][i].first.first, aristas[v.first][v.second][i].first.second));
				}
			}
		}
	}

	cout << dist[fin.first][fin.second] << '\n';
}




	int main()	{
		char aux;
		int n;
		while (cin >> f >> c) {
			vector<vector<vector<pair<pair<int, int>, int>>>> aristas(f, vector<vector<pair<pair<int, int>, int>>>(c));
			for (int i = 0; i < f; ++i) {
				cin.get(aux);
				for (int j = 0; j < c; ++j) {
					cin.get(aux);
					for (int k = 0; k < 8; ++k) {
						if (k!= int(aux) - int('0') && ok(i + df[k], j + dc[k]))aristas[i][j].push_back({ {i + df[k], j + dc[k]}, 1 });
					}
					if (ok(i + df[int(aux) - int('0')], j + dc[int(aux) - int('0')])) {
						aristas[i][j].push_back({ {i + df[int(aux) - int('0')], j + dc[int(aux) - int('0')]}, 0});
					}
				}
			}
			cin >> n;
			while (n--) {
				cin >> ini.first >> ini.second >> fin.first >> fin.second;
				ini.first--; ini.second--; fin.first--; fin.second--;
				resuelve(ini, aristas);
			}
		}
		return 0;
	}


