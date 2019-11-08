#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

using vvi = vector<vector<int>>;
int nreg;

void bfs(int s, int t, const vvi &cap, vector<int> &parent, vector<bool> &visited)
{
	queue<int> q;
	q.push(s);
	parent[s] = -1;
	visited[s] = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (u == t)
			break;
		for (int i = 0; i < 2 * nreg + 2; ++i)
		{
			if (cap[u][i] == 0)
				continue;
			if (!visited[i])
			{
				parent[i] = u;
				visited[i] = true;
				q.push(i);
			}
		}
	}
}

void solucion()
{
	vvi cap(2 * nreg + 2, vector<int>(2 * nreg + 2, 0));
	for (int i = 0; i < nreg; ++i)
	{
		int regaux;
		cin >> regaux;
		cap[i + 1][i + 1 + nreg] = regaux;
	}
	int a;
	cin >> a;
	for (int i = 0; i < a; ++i)
	{
		int v1, v2, cp;
		cin >> v1 >> v2 >> cp;
		cap[v1 + nreg][v2] += cp;
	}
	int b, d;
	cin >> b >> d;
	for (int i = 0; i < b; ++i)
	{
		int reg;
		cin >> reg;
		cap[0][reg] = 1000000000;
	}

	for (int i = 0; i < d; ++i)
	{
		int reg;
		cin >> reg;
		cap[reg + nreg][2 * nreg + 1] = 1000000000;
	}

	int ret = 0;
	int sol;
	do
	{
		vector<int> parent(2 * nreg + 2);
		vector<bool> visited(2 * nreg + 2, false);
		sol = 1000000000;
		bfs(0, 2 * nreg + 1, cap, parent, visited);
		if (!visited[2 * nreg + 1])
			sol = 0;
		else
		{
			int v = 2 * nreg + 1;
			while (v != 0)
			{
				sol = min(cap[parent[v]][v], sol);
				v = parent[v];
			}
			v = 2 * nreg + 1;
			while (v != 0)
			{
				cap[parent[v]][v] -= sol;
				cap[v][parent[v]] += sol;
				v = parent[v];
			}
		}
		ret += sol;
	} while (sol > 0);
	cout << ret << '\n';
}

int main()
{
	while (cin >> nreg)
	{
		solucion();
	}

	return 0;
}