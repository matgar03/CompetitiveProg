
#include <iostream> 
#include <vector>
#include <set>
#include <queue>
#include <climits>

using namespace std;
int n;
int mkx[] = { -2,-1,1,2,2,1,-1,-2 };
int mky[] = { 1,2,2,1,-1,-2,-2,-1 };
int mbx[] = { -2,2,2,-2 };
int mby[] = { 2,2,-2,-2 };
using ii= pair<int, int>;
using iiii=pair<pair<int, int>, pair<int,int>> ;
bool ok(int i, int j, const vector<vector<int>>& m) {
	return (i >= 0 && j >= 0 && i < n && j < n);

}


void solucion() {
	ii ini;
	ii fin;
	cin >> ini.first >> ini.second >> fin.first >> fin.second;
	--ini.first; --ini.second; --fin.first; --fin.second;
	ii aux;
	cin >> aux.first >> aux.second;
	vector<vector<int>> m(n, vector<int>(n, 0));
	while (aux.first != 0 || aux.second != 0) {
		if (ok(aux.first - 1, aux.second - 1, m)) {
			m[aux.first - 1][aux.second - 1] = 7;
			cin >> aux.first >> aux.second;
		}
	}

	queue<iiii> q;
	q.push({ ini,{1,0 } });
	q.push({ ini,{2,0 } });
	q.push({ ini,{4,0} });
	m[ini.first][ini.second] = 7;
	bool enc = false;
	int sol;
	iiii posmov;

	while (!q.empty() && !enc) {
		posmov = q.front();
		q.pop();
		if (fin == ii(posmov.first.first, posmov.first.second)) {
			enc = true;
			sol = posmov.second.second ;
		}
		else if (posmov.second.first == 1) {
			for (int i = 0; i < 8 && !enc; ++i) {
				if (ok(posmov.first.first + mkx[i], posmov.first.second + mky[i], m)) {
					if (m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] != 2 && m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] != 3 && m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] != 6 && m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] != 7) {
						m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] += 2;
						q.push({ {posmov.first.first + mkx[i],posmov.first.second + mky[i]},{2,posmov.second.second + 1} });

					}
					if (m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] != 4 && m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] != 5 && m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] != 6 && m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] != 7) {
						m[posmov.first.first + mkx[i]][posmov.first.second + mky[i]] += 4;
						q.push({ {posmov.first.first + mkx[i],posmov.first.second + mky[i]},{4,posmov.second.second + 1} });
					}
				}
			}
		}
		else if (posmov.second.first == 2) {
			for (int i = 0; i < 4 && !enc; ++i) {
				if (ok(posmov.first.first + mbx[i], posmov.first.second + mby[i], m)) {
					if (m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] != 1 && m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] != 3 && m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] != 5 && m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] != 7) {
						m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] += 1;
						q.push({ {posmov.first.first + mbx[i],posmov.first.second + mby[i]},{1,posmov.second.second + 1} });
					}
					if (m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] != 4 && m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] != 5 && m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] != 6 && m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] != 7) {
						m[posmov.first.first + mbx[i]][posmov.first.second + mby[i]] += 4;
						q.push({ {posmov.first.first + mbx[i],posmov.first.second + mby[i]},{4,posmov.second.second + 1} });
					}
				}
			}
		}
		else {
			if (m[n-1- posmov.first.first][posmov.first.second] != 1 && m[n-1- posmov.first.first][posmov.first.second] != 3 && m[n-1- posmov.first.first][posmov.first.second] != 5 && m[n-1- posmov.first.first][posmov.first.second] != 7) {
				m[n-1- posmov.first.first][posmov.first.second] += 1;
				q.push({ {n-1- posmov.first.first,posmov.first.second },{1,posmov.second.second + 1} });
			}
			if (m[n-1- posmov.first.first][posmov.first.second] != 2 && m[n-1- posmov.first.first][posmov.first.second] != 3 && m[n-1- posmov.first.first][posmov.first.second] != 6 && m[n-1- posmov.first.first][posmov.first.second] != 7) {
				m[n-1- posmov.first.first][posmov.first.second] += 2;
				q.push({ {n-1- posmov.first.first,posmov.first.second },{2,posmov.second.second + 1} });
			}
			if (m[posmov.first.first][n-1-posmov.first.second] != 1 && m[posmov.first.first][n-1-posmov.first.second] != 3 && m[posmov.first.first][n-1-posmov.first.second] != 5 && m[posmov.first.first][n-1-posmov.first.second] != 7) {
				m[posmov.first.first][n-1-posmov.first.second] += 1;
				q.push({ {posmov.first.first,n-1-posmov.first.second },{1,posmov.second.second + 1} });
			}
			if (m[posmov.first.first][n-1-posmov.first.second] != 2 && m[posmov.first.first][n-1-posmov.first.second] != 3 && m[posmov.first.first][n-1-posmov.first.second] != 6 && m[posmov.first.first][n-1-posmov.first.second] != 7) {
				m[posmov.first.first][n-1-posmov.first.second] += 2;
				q.push({ {posmov.first.first,n-1-posmov.first.second },{2,posmov.second.second + 1} });
			}

		}

	}
	if (enc) cout << "Result : "<<sol<<'\n';
	else cout << "Solution doesn't exist\n";


}

int main() {
	cin >> n;
	while (n) {
		n *= 2;
		solucion();
		cin >> n;
	}

	return 0;
}