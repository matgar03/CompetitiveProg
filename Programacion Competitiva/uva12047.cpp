#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using vvii = vector<vector<pair<int, int>>>;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using viii = vector<pair<int, ii>>;
;
int INF = 1000000000;

//mirar longes

void dijkstra(int s, vi &dist, vvii &adjList)
{
    dist.assign(adjList.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, s});
    while (!pq.empty())
    {
        ii front = pq.top();
        pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u])
            continue;
        for (auto a : adjList[u])
        {
            if (dist[u] + a.first < dist[a.second])
            {
                dist[a.second] = dist[u] + a.first;
                pq.push({dist[a.second], a.second});
            }
        }
    }
}

void sol()
{
    int N, M, s, t, p;
    cin >> N >> M >> s >> t >> p;
    --s;
    --t;
    vvii grafo(N);
    vvii inv(N);
    viii ar(M);
    for (int i = 0; i < M; ++i)
    {
        int a1, a2, a3;
        cin >> a1 >> a2 >> a3;
        --a1;
        --a2;
        grafo[a1].push_back({a3, a2});
        inv[a2].push_back({a3, a1});
        ar[i] = {a3, {a1, a2}};
    }
    vi d1(N, INF);
    vi d2(N, INF);
    dijkstra(s, d1, grafo);
    dijkstra(t, d2, inv);
    sort(ar.begin(), ar.end());
    int sol = -1;
    for (int i = M - 1; i >= 0; --i)
    {
        if ((ar[i].first + d1[ar[i].second.first] + d2[ar[i].second.second] <= p))
        {
            sol = ar[i].first;
            break;
        }
    }
    cout << sol << '\n';
}

int main()
{
    int casos;
    cin >> casos;
    while (casos--)
    {
        sol();
    }

    return 0;
}