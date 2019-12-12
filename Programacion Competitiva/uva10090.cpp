#include <iostream>
#include <cmath>
using namespace std;

long long int n;

int extendedEuclidRec(long long int a, long long int b, long long int &u, long long int &v)
{
    if (!b)
    {
        u = 1;
        v = 0;
        return a;
    }
    int r = extendedEuclidRec(b, a % b, u, v);
    int uAux = v;
    int vAux = u - (a / b) * v;
    u = uAux;
    v = vAux;
    return r;
}

void solucion()
{
    long long int c1, n1, c2, n2;
    cin >> c1 >> n1 >> c2 >> n2;
    long long int u, v;
    long long int mcd = extendedEuclidRec(n1, n2, u, v);

    if (n % mcd != 0 || (n < n1) && (n < n2))
    {
        cout << "failed\n";
        return;
    }
    long long int x1, y1;
    x1 = u * (n / mcd);
    y1 = v * (n / mcd);
    long long int sup = floor(y1 * (double)mcd / n1);
    long long int inf = ceil(-x1 * (double)mcd / n2);
    long long int i1, i2, s1, s2;
    i1 = x1 + inf * (n2 / mcd);
    i2 = y1 - inf * (n1 / mcd);
    s1 = x1 + sup * (n2 / mcd);
    s2 = y1 - sup * (n1 / mcd);

    if (c1 * s1 + c2 * s2 < c1 * i1 + c2 * i2 && (s1 >= 0) && s2 >= 0)
    {
        cout << s1 << ' ' << s2 << '\n';
    }
    else if (i1 >= 0 && i2 >= 0)
        cout << i1 << ' ' << i2 << '\n';
    else
        cout << "failed\n";
}

int main()
{
    cin >> n;
    while (n != 0)
    {
        solucion();
        cin >> n;
    }
}