#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

using T = double; // using T = int;
int C;

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
    // bool operator<(pt o) const { // #define EPS 1e-9
    // if (fabs(x - o.x) < EPS) return y < o.y;
    // return x < o.x;
    // }
};

T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }

T sq(pt v) { return v.x * v.x + v.y * v.y; }
double abs(pt v) { return sqrt(sq(v)); }

double dist(pt a, pt b)
{ // Euclidean distance
    return hypot(a.x - b.x, a.y - b.y);
}
T dist2(pt a, pt b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }
bool isPerp(pt v, pt w) { return dot(v, w) == 0; }
double angle(pt v, pt w)
{ // [0..PI]
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

// positivo/cero/negativo: c a la izquierda/sobre/derecha de a-b
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

const double PI = acos(-1);
double orientedAngle(pt a, pt b, pt c)
{
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    else
        return 2 * PI - angle(b - a, c - a);
}

pt translate(pt v, pt p) { return p + v; }
// scale p by a certain factor around a center c
pt scale(pt c, double factor, pt p)
{
    return c + (p - c) * factor;
}
// rotate p by a certain angle a counter-clockwise around origin
pt rotate(pt p, double a)
{
    return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}

// rotate 90º counterclockwise
pt perp(pt p) { return {-p.y, p.x}; }

struct line
{
    pt v;
    T c;
    // from direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {}
    // from equation ax + by = c
    line(T a, T b, T c) : v({b, -a}), c(c) {}
    // from points p and q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}

    T side(pt p) { return cross(v, p) - c; }

    double dist(pt p) { return abs(side(p)) / abs(v); }

    pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
};

bool inter(line l1, line l2, pt &out)
{
    T d = cross(l1.v, l2.v);
    if (d == 0)
        return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    // requires floating-point coordinates
    return true;
}

double suma(int i, vector<pt> &v, double max)
{
    line r(v[i], v[i + 1]);
    pt horiz;
    horiz.x = 1;
    horiz.y = 0;
    line hor(horiz, max);
    pt intersec;
    intersec.x = intersec.y = 0;
    inter(r, hor, intersec);
    return dist(v[i], intersec);
}

double sol(vector<pt> &v)
{
    double max = 0, solucion = 0;
    for (int i = v.size() - 2; i >= 0; --i)
    {
        if (v[i].y > max)
        {
            solucion += suma(i, v, max);
            max = v[i].y;
        }
    }
    cout << solucion << '\n';
    return solucion;
}

int main()
{
    cin >> C;
    cout << fixed << setprecision(2);
    int n;
    while (C--)
    {
        cin >> n;
        vector<pt> v(n);
        for (int i = 0; i < n; ++i)
            cin >> v[i].x >> v[i].y;
        sort(v.begin(), v.end());
        sol(v);
    }
    return 0;
}