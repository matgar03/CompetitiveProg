#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using T = int; // using T = int;
struct pt
{
    T x, y;
    pt operator+(pt p) const { return {x + p.x, y + p.y}; }
    pt operator-(pt p) const { return {x - p.x, y - p.y}; }
    pt operator*(T d) const { return {x * d, y * d}; }
    pt operator/(T d) const { return {x / d, y / d}; } // only for floating-point

    bool operator==(pt o) const { return x == o.x && y == o.y; }
    bool operator!=(pt o) const { return !(*this == o); }
    bool operator<(pt o) const
    { // sort points lexicographically
        if (x == o.x)
            return y < o.y;
        return x < o.x;
    }
};

void dividir(pt act, vector<pt> &v, int consider, priority_queue<pair<int, pair<vector<pt>, int>>> &q)
{
    ++consider;
    vector<pt> aux(4);
    aux[0] = v[0];
    aux[1] = v[1];
    aux[2] = v[2];
    aux[2].y += act.y;
    aux[3] = v[3];
    aux[3].y += act.y;
    q.push({(aux[0].y - aux[2].y) * (aux[1].y - aux[3].y), {aux, consider}});
    aux[0] = aux[2];
    aux[1] = aux[3];
    aux[2] = v[2];
    aux[3] = v[3];
    q.push({(aux[0].y - aux[2].y) * (aux[1].y - aux[3].y), {aux, consider}});
    aux[0] = v[0];
    aux[1] = v[0];
    aux[1].x += act.x;
    aux[2] = v[2];
    aux[3] = v[2];
    aux[3].x += act.x;
    q.push({(aux[0].y - aux[2].y) * (aux[1].y - aux[3].y), {aux, consider}});
    aux[0] = aux[1];
    aux[2] = aux[3];
    aux[1] = v[1];
    aux[3] = v[3];
    q.push({(aux[0].y - aux[2].y) * (aux[1].y - aux[3].y), {aux, consider}});
}

void sol()
{
    int a, l;
    cin >> a >> l;
    int k;

    cin >> k;

    vector<pt> arb;
    while (k != 0)
    {
        int x, y, dx, dy;
        cin >> x >> y;
        arb.push_back(pt({x, y}));

        if (k > 1)
        {
            cin >> dx >> dy;
        }

        for (int i = 1; i < k; ++i)
        {
            arb.push_back(pt({x + i * dx, y + i * dy}));
        }

        cin >> k;
    }
    priority_queue<pair<int, pair<vector<pt>, int>>> q;
    pt ui, ud, di, dd;
    ui = pt({0, l});
    ud = pt({a, l});
    di = pt({0, 0});
    dd = pt({a, 0});
    vector<pt> v(4);
    v[0] = ui;
    v[1] = ud;
    v[2] = di;
    v[3] = dd;
    q.push({a * l, {v, 0}});
    bool fin = false;
    int solucion;
    while (!fin)
    {
        if (q.top().second.second == arb.size())
            fin = true;
        else
        {
            pt act = arb[q.top().second.second];
            for (int i = 0; i < 4; ++i)
                v[i] = q.top().second.first[i];
            int consider = q.top().second.second;
            q.pop();
            dividir(act, v, consider, q);
        }
    }
    cout << q.top().first << '\n';
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