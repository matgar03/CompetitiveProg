#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <assert.h>




using namespace std;
int N, instr;

vector<int> sol;


using T = double; // using T = int;
struct pt
{
	T x, y;
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
	} //   bool operator<(pt o) const {   // #define EPS 1e-9
	//       if (fabs(x - o.x) < EPS) return y < o.y;
	//       return x < o.x; //   }
};

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

T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }

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
pt scale(pt c, double factor, pt p) { return c + (p - c) * factor; }

// rotate p by a certain angle a counter-clockwise around origin
pt rotate(pt p, double a) { return { p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a) }; }

// rotate 90º counterclockwise
pt perp(pt p) { return { -p.y, p.x }; }

bool half(pt p)
{
	assert(p.x != 0 || p.y != 0);
	return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<pt>& v)
{
	sort(v.begin(), v.end(), [](pt v, pt w) { return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v, w), sq(w)); });
}

struct line
{
	pt v;
	T c;                                      // from direction vector v and offset c
	line(pt v, T c) : v(v), c(c) {}           // from equation ax + by = c
	line(T a, T b, T c) : v({ b, -a }), c(c) {} // from points p and q
	line(pt p, pt q) : v(q - p), c(cross(v, p)) {}
	T side(pt p) { return cross(v, p) - c; }
	double dist(pt p) { return abs(side(p)) / abs(v); }
	pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
};

bool inter(line l1, line l2, pt& out)
{
	T d = cross(l1.v, l2.v);
	if (d == 0)
		return false;
	out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
	return true;
}

double areaTriangle(pt a, pt b, pt c)
{
	return abs(cross(b - a, c - a)) / 2.0;
}

double areaPolygon(vector<pt> const& p)
{
	double area = 0.0;
	for (int i = 0; i < int(p.size()) - 1; ++i)
	{
		area += cross(p[i], p[i + 1]);
	}
	return abs(area) / 2.0;
}

// devuelve true si r está en el lado izquierdo de la línea pq
bool ccw(pt p, pt q, pt r)
{
	return orient(p, q, r) > 0; // >= para puntos colineales
} // devuelve un polígono con la envolvente convexa de la nube de puntos P
vector<pt> convexHull(vector<pt>& P)
{
	int n = int(P.size()), k = 0;
	vector<pt> H(2 * n);
	sort(P.begin(), P.end()); // build lower hull
	for (int i = 0; i < n; ++i)
	{
		while (k >= 2 && !ccw(H[k - 2], H[k - 1], P[i]))
			--k;
		H[k++] = P[i];
	} // build upper hull
	for (int i = n - 2, t = k + 1; i >= 0; --i)
	{
		while (k >= t && !ccw(H[k - 2], H[k - 1], P[i]))
			--k;
		H[k++] = P[i];
	}
	H.resize(k);
	return H;
}

vector<pt> cutPolygon(pt a, pt b, vector<pt> const& P)
{
	vector<pt> R;
	pt c;
	for (int i = 0; i < int(P.size()) - 1; i++)
	{
		double left1 = cross(b - a, P[i] - a), left2 = cross(b - a, P[i + 1] - a);
		if (left1 >= 0)
			R.push_back(P[i]); // P[i] is on the left of ab
		if (left1 * left2 < 0)
		{ // edge (P[i], P[i+1]) crosses line ab
			inter({ P[i], P[i + 1] }, { a, b }, c);
			R.push_back(c);
		}
	}
	if (!R.empty())
		R.push_back(R[0]); // make R's first point = R’s last point
	return R;
}


void mover(pair<pair<double, double>, int> &act,string ord, int cant) {
	if (ord == "fd") {
		act.first.first += cant * sin(act.second * PI / 180);
		act.first.second += cant * cos(act.second * PI / 180);
	}
	else if (ord == "bk") {
		act.first.first -= cant * sin(act.second * PI / 180);
		act.first.second -= cant * cos(act.second * PI / 180);
	}
	else if (ord == "lt") {
		act.second += cant; act.second = act.second % 360;
	}
	else {
		act.second -= cant; act.second = act.second % 360;
	}
}

int main() {
	cin >> N;
	string aux1,aux2, ord;
	
	int num;
	while (N--) {
		pair<pair<double, double>, int> act = { {0.0, 0.0}, 0 }, quest;
		cin >> instr;
		for (int i = 0; i < instr; ++i) {
			cin >> aux1 >> aux2;
			if (aux2 != "?") {
				stringstream c(aux2);
				c >> num;
				mover(act, aux1, num);
			}
			else {
				quest = act;
				ord = aux1;
			}
		}
		if (ord == "fd" || ord == "bk") {
			int aux = round(sqrt(act.first.first * act.first.first + act.first.second * act.first.second));
			cout << aux << '\n';
		}
		else {
			if (round(act.first.first) == 0 && round(act.first.second) == 0)cout << "0\n";
			else {
				pt p1, p2, p3;
				p1.x = p2.y = 0;
				p2.x = -quest.first.first;
				p2.y = -quest.first.second;
				p3.x = act.first.first-p2.x;
				p3.y = act.first.second-p2.y;
				double ori = cross(p2,p3);
				double aux3 = -1.0 * quest.first.first * (act.first.first - quest.first.first) + -1.0 * quest.first.second * (act.first.second - quest.first.second);
				double aux4=sqrt((act.first.first - quest.first.first) * (act.first.first - quest.first.first) + (act.first.second - quest.first.second) * (act.first.second - quest.first.second));
				double aux6 = sqrt(quest.first.first * quest.first.first + quest.first.second * quest.first.second);
				int aux5 = round(180 * acos(aux3/(aux4*aux6)) / PI);
				/*if (act.first.first < 0) {
					aux5 = 360 - aux5;
				}*/
				if (ord == "lt") {
					if (ori >= 0.0)cout << aux5 << '\n';
					else cout << 360 - aux5 << '\n';
				}
					//sol.push_back(aux5);
				else {
					if (ori <= 0.0)cout << aux5 << '\n';
					else cout << 360 - aux5 << '\n';
				}
					//sol.push_back(360 - aux5);
			}
			/*(-1.0 * quest.first.first * (act.first.first - quest.first.first)) + -1.0 * quest.first.second * (act.first.second - quest.first.second) / (sqrt((act.first.first - quest.first.first) * (act.first.first - quest.first.first) + (act.first.second - quest.first.second) * (act.first.second - quest.first.second)) * sqrt(quest.first.first * quest.first.first + quest.first.second * quest.first.second))*/
		}
	}
	return 0;
}