#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

int a, b, c, d;

vector<pair<int,int>> soluc;
/*
void mcd(int m, int n, int &aux)
{
	int r = m % n;
	while (r != 0)
	{
		r = m % n;
		m = n;
		n = r;
	}
	aux = m;
}
*/
void solucion() {
	set<pair<pair<int, int>, int>> mapa;
	priority_queue<pair<pair<int, int>, pair<int, int>>> q;
	/*
	if (c >= a) {
		q.push({ {-a,a},{0,c - a} });
	}
	else {
		q.push({ {-c,c},{0,0} });
	}
	if (c >= b) {
		q.push({ {-b,0},{b,c - b} });
	}
	else {
		q.push({ {-c,0},{c,0} });
	}*/
	pair<int, int> sol = { 0,0 };
	q.push({ {0, 0},{0,c} });
	bool enc = false;
	pair<pair<int, int>, pair<int, int>> act;
	while (!q.empty() && !enc) {
		act = q.top(); q.pop();
		if (!mapa.count({ {act.first.second,act.second.first},act.second.second })) {
			mapa.insert({ {act.first.second, act.second.first}, act.second.second });
			if (act.first.second == d || act.second.first == d || act.second.second == d) {
				enc = true;
				sol.first = d;
				sol.second = act.first.first;
			}
			if (sol.first < act.first.second && act.first.second < d) {
				sol.first = act.first.second;
				sol.second = act.first.first;
			}
			if (sol.first < act.second.first && act.second.first < d){
				sol.first = act.second.first;
				sol.second = act.first.first;
			}
			if (sol.first < act.second.second && act.second.second < d){
				sol.first = act.second.second;
				sol.second = act.first.first;
			}
			if (!enc) {
				if (act.first.second > 0) {
					if (act.second.first < b) {
						if (b - act.second.first >= act.first.second) {
							q.push({ {act.first.first - act.first.second,0}, {act.first.second + act.second.first, act.second.second} });
						}
						else q.push({ {act.first.first - b + act.second.first,act.first.second - b + act.second.first}, {b, act.second.second} });
					}
					if (act.second.second < c) {
						if (c - act.second.second >= act.first.second) {
							q.push({ {act.first.first - act.first.second,0}, {act.second.first,act.first.second + act.second.second} });
						}
						else q.push({ {act.first.first - c + act.second.second,act.first.second - c + act.second.second}, {act.second.first, c} });

					}
				}
				if (act.second.first > 0) {
					if (act.first.second < a) {
						if (a - act.first.second >= act.second.first) {
							q.push({ {act.first.first - act.second.first,act.first.second + act.second.first}, {0, act.second.second} });
						}
						else q.push({ {act.first.first - a + act.first.second,a}, {act.second.first - a + act.first.second, act.second.second} });
					}
					if (act.second.second < c) {
						if (c - act.second.second >= act.second.first) {
							q.push({ {act.first.first - act.second.first,act.first.second }, {0, act.second.second + act.second.first} });
						}
						else q.push({ {act.first.first - c + act.second.second,act.first.second}, {act.second.first - c + act.second.second,c} });

					}
				}

				if (act.second.second > 0) {
					if (act.first.second < a) {
						if (a - act.first.second >= act.second.second) {
							q.push({ {act.first.first - act.second.second,act.first.second + act.second.second}, {act.second.first, 0} });
						}
						else q.push({ {act.first.first - a + act.first.second,a}, {act.second.first , act.second.second - a + act.first.second} });
					}
					if (act.second.first < b) {
						if (b - act.second.first >= act.second.second) {
							q.push({ {act.first.first - act.second.second,act.first.second}, {act.second.first + act.second.second, 0} });
						}
						else q.push({ {act.first.first - b + act.second.first,act.first.second}, {b, act.second.second - b + act.second.first} });
					}
				}



			}
		}
	}
	soluc.push_back({ -sol.second,sol.first });
	cout << -sol.second << ' ' << sol.first << '\n';
	//sol.push_back({ -act.first.first,d });

}



int main() {
	int n;
	cin >> n;
	while (n--) {
		int m;
		cin >> a >> b >> c >> d;
		if (c <= d) cout << 0 << ' ' << c << '\n';
		else solucion();
		/*else {
			if (c <= b && c <= a) cout << 0 << ' ' << 0 << '\n';
			else if (c <= b && c < a) {
				if (a <= d) cout << 0 << ' ' << a << '\n';
				else cout << 0 << ' ' << 0 << '\n';
			}
			else if (c <= a && c < b) {
				if (b <= d) cout << 0 << ' ' << b << '\n';
				else cout << 0 << ' ' << 0 << '\n';
			}
			else {
				if (a<b) {
					m = a;
					while (m <= d && m <= b) {
						m += a;
					}
					m -= a;
					d = m;
				}
				else {
					m = b;
					while (m <= d && m <= a) {
						m += b;
					}
					m -= b;
					d = m;
				}
				if (d == 0 || d == c)cout << 0 << ' ' << d << '\n';
				else solucion();
			}
		}*/
	}
	/*
	cout << '\n' << '\n';
	for (int i = 0; i < soluc.size(); ++i) {
		cout << soluc[i].first << ' ' << soluc[i].second << '\n';
	}
	*/
	return 0;
}