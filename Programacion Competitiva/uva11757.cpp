#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
int L, W, N, d, caso;
using vvii = vector<vector<pair<int, int>>>;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using viii = vector<pair<int, ii>>;

bool dist(ii p1, ii p2)
{
    return sqrt(1.0 * (p1.first - p2.first) * (p1.first - p2.first) + 1.0 * (p1.second - p2.second) * (p1.second - p2.second)) <= d;
}

void bfs(int s, int t)
{
    queue<int> q;
    memset(visited, 0, sizeof(visited));
    q.push(s);
    parent[s] = -1;
    visited[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == t)
            break;
        for (int i = 0; i < adj[u].size(); ++i)
        {
            int v = adj[u][i];
            if (!visited[v] && (cap[u][v] > 0))
            {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int sendFlow(int s, int t)
{
    // Intentamos llegar de s a t
    bfs(s, t);
    if (!visited[t])
        return 0; // No pudimos
    // Buscamos capacidad m´as peque˜na en el camino
    int flow = INF, v = t;
    while (v != s)
    {
        flow = min(cap[parent[v]][v], flow);
        v = parent[v];
    }
    // Mandamos flujo
    v = t;
    while (v != s)
    {
        cap[parent[v]][v] -= flow;
        cap[v][parent[v]] += flow; // INVERSA
        v = parent[v];
    }
}
int edmonKarps(int s, int t)
{
    int ret = 0;
    int flow = 0;
    do
    {
        flow = sendFlow(s, t);
        ret += flow;
    } while (flow > 0);
    return ret;
}

int main()
{
    cin >> L >> W >> N >> d;
    caso = 1;
    while (L != 0 || W != 0 || N != 0 || d != 0)
    {
        vii def(N);
        vvii grafo(2 * N + 2);
        int a1, a2;
        for (int i = 0; i < N; ++i)
        {
            cin >> a1 >> a2;
            def[i] = {a1, a2};
        }
        for (int i = 0; i < N; ++i)
        {
            grafo[i].push_back({1, i + N});

            for (int j = 0; j < N; ++j)
            {
                if (i == j)
                    continue;

                if (dist(def[i], def[j]))
                {
                    grafo[i + N].push_back({1, j});
                }
                if (def[i].second + d >= W)
                    grafo[2 * N].push_back({1, i});
                if (def[i].second - d <= 0)
                    grafo[i + N].push_back({1, 2 * N + 1});
            }
        }

        cin >> L >> W >> N >> d;
        ++caso;
    }
    return 0;
}