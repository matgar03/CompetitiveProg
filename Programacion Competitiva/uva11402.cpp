#include <iostream>
#include <vector>
#include <string>

using namespace std;

int caso;

class SegmentTree
{
    vector<int> st;
    vector<int> lazy;
    int tam;

public:
    SegmentTree(int maxN)
    {
        st.reserve(4 * maxN + 10);
        lazy.reserve(4 * maxN + 10);
    }
    int query(int a, int b)
    {
        return query(1, 0, tam - 1, a, b);
    }
    int query(int vertex, int L, int R, int i, int j)
    {
        pushLazyUpdate(vertex, L, R);
        if ((j < L) || (R < i))
            return 0;
        if (i <= L && R <= j)
            return st[vertex];
        int mitad = (L + R) / 2;
        return query(2 * vertex, L, mitad, i, j) +
               query(2 * vertex + 1, mitad + 1, R, i, j);
    }
    void updateRange(int a, int b, int op)
    {
        updateRange(1, 0, tam - 1, a, b, op);
    }
    void updateRange(int vertex, int L, int R,
                     int a, int b, int op)
    {

        pushLazyUpdate(vertex, L, R);
        if ((b < L) || (R < a))
            return;

        if ((a <= L) && (R <= b))
        {
            if (op == 1)
            {
                st[vertex] = R - L + 1;
            }
            else if (op == 2)
            {
                st[vertex] = 0;
            }
            else
            {
                st[vertex] = (R - L + 1) - st[vertex];
            }
            setLazyUpdate(2 * vertex, op);
            setLazyUpdate(2 * vertex + 1, op);
            return;
        }

        int m = (L + R) / 2;
        updateRange(2 * vertex, L, m, a, b, op);
        updateRange(2 * vertex + 1, m + 1, R, a, b, op);

        st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
    }
    void setLazyUpdate(int vertex, int value) //este es el metodo
    {

        if (value == 1 || value == 2)
        {
            lazy[vertex] = value;
        }
        else if (value == 3)
        {
            lazy[vertex] = cambio(lazy[vertex]);
        }
    }
    void pushLazyUpdate(int vertex, int L, int R)
    {
        if (lazy[vertex] != 0)
        {

            if (lazy[vertex] == 1)
            {
                st[vertex] = R - L + 1;
            }
            else if (lazy[vertex] == 2)
            {
                st[vertex] = 0;
            }
            else
            {
                st[vertex] = (R - L + 1) - st[vertex];
            }
        }
        if (L != R)
        {
            // Tenemos hijos
            int m = (L + R) / 2;
            setLazyUpdate(2 * vertex, lazy[vertex]);
            setLazyUpdate(2 * vertex + 1, lazy[vertex]);
        }

        lazy[vertex] = 0;
    }
    int cambio(int v)
    {
        return 3 - v;
    }
    void build(const string &s, int n)
    {
        tam = n;
        build(s, 1, 0, n - 1);
    }
    void build(const string &s, int p, int l, int r)
    {
        if (l == r)
        {
            if (s[l] == '0')
                st[p] = 0;
            else
                st[p] = 1;
            return;
        }
        int m = (l + r) / 2;
        build(s, 2 * p, l, m);
        build(s, 2 * p + 1, m + 1, r);
        st[p] = st[2 * p] + st[2 * p + 1];
        lazy[p] = 0;
    }
};

void solucion()
{
    string pir;
    int m;
    cin >> m;
    int el, con;
    string aux;
    for (int i = 0; i < m; ++i)
    {
        cin >> el;
        cin >> aux;
        for (int j = 0; j < el; ++j)
        {
            pir += aux;
        }
    }

    int tam = pir.length();

    SegmentTree sg(1024000);

    sg.build(pir, tam);

    int god;
    cin >> god;
    char c;
    int a1, a2;
    cout << "Case " << caso << ":\n";
    int q = 1;
    for (int i = 0; i < god; ++i)
    {

        cin >> c >> a1 >> a2;
        if (c == 'F')
        {
            sg.updateRange(a1, a2, 1);
        }
        else if (c == 'E')
        {
            sg.updateRange(a1, a2, 2);
        }
        else if (c == 'I')
        {
            sg.updateRange(a1, a2, 3);
        }
        else if (c == 'S')
        {
            cout << "Q" << q << ": " << sg.query(a1, a2) << '\n';
            ++q;
        }
    }
}

int main()
{
    int n;
    caso = 1;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        solucion();
        caso++;
    }
    return 0;
}