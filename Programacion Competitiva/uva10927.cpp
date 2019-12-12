#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <assert.h>
#include <tuple>

#include <fstream>

using namespace std;

//using T = double;
using T = int;
int N;

struct pt
{
	T x, y, z;
	pt operator+(pt p) const { return { x + p.x, y + p.y }; }
	pt operator-(pt p) const { return { x - p.x, y - p.y }; }
	pt operator*(T d) const { return { x * d, y * d }; }
	pt operator/(T d) const { return { x / d, y / d }; } // only for floating-point

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
/*
pt rotate(pt p, double a)
{
	return { p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a) };
}
*/
// rotate 90º counterclockwise
pt perp(pt p) { return { -p.y, p.x }; }

bool half(pt p)
{
	assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
	return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<pt>& v)
{
	sort(v.begin(), v.end(), [](pt v, pt w) {
		return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v, w), sq(w));
		});
}

struct line
{
	pt v;
	T c;
	// from direction vector v and offset c
	line(pt v, T c) : v(v), c(c) {}
	// from equation ax + by = c
	line(T a, T b, T c) : v({ b, -a }), c(c) {}
	// from points p and q
	line(pt p, pt q) : v(q - p), c(cross(v, p)) {}

	T side(pt p) { return cross(v, p) - c; }

	double dist(pt p) { return abs(side(p)) / abs(v); }

	pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
};

int sgn(int val) {
	if (val > 0) return 1;
	else if (val < 0)return -1;
	else return 0;
}

bool inter(line l1, line l2, pt& out)
{
	T d = cross(l1.v, l2.v);
	if (d == 0)
		return false;
	out = (l2.v * l1.c - l1.v * l2.c) / d;
	// requires floating-point coordinates
	return true;
}

void sol(vector<pt>& v)
{
	vector<pt> tapados;
	bool linea;
	pt ori;
	ori.x = ori.y = 0;
	for (int i = 0; i < N; ++i)
	{
		int max = v[i].z;
		linea = true;
		while (linea && i < N-1)
		{
			linea = false;
			line l = line(ori, v[i]);
			++i;
			if (l.dist(v[i])==0 && sgn(v[i].x)==sgn(v[i-1].x)&&sgn(v[i].y)==sgn(v[i-1].y))
			{
				linea = true;
				if (v[i].z <= max)
					tapados.push_back(v[i]);
				else
					max = v[i].z;
			}
			else
				--i;
		}
	}
	sort(tapados.begin(), tapados.end());
	if (tapados.size() == 0) {
		cout << "All the lights are visible.\n";
	}

	else
	{
		cout << "Some lights are not visible:\n";
		if (tapados.size()>1)cout << "x = " << tapados[0].x << ", y = " << tapados[0].y << ";\n";
		for (int i = 1; i < tapados.size() - 1; ++i)
			cout << "x = " << tapados[i].x << ", y = " << tapados[i].y << ";\n";
		cout << "x = " << tapados[tapados.size() - 1].x << ", y = " << tapados[tapados.size() - 1].y << ".\n";
	}
}

int main()
{
	cin >> N;
	int cont = 1;
	// Crea un fichero de salida
	while (N)
	{
		vector<pt> v(N);
		for (int i = 0; i < N; ++i)
			cin >> v[i].x >> v[i].y >> v[i].z;

		polarSort(v);
		cout << "Data set " << cont << ":\n";
		sol(v);
		
		++cont;
		cin >> N;
	}
	return 0;
}