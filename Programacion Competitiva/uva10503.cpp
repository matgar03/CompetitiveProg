#include <iostream>
#include <vector>

using namespace std;

int n, m, pri, ult;
bool fin;

void resuelve(vector<pair<int, int>> v, vector<bool> marked) {
	for (int i = 0; i < m && !fin; ++i) {
		if (!marked[i]) {
			if (v[i].first == pri) {
				marked[i] = true;
				pri = v[i].second;
				--n;
				if (n == 0 && pri == ult) {
					fin = true;
				}
				else {
					resuelve(v, marked);
					++n;
					marked[i] = false;
					pri = v[i].first;
				}
			}
			else if (v[i].second == pri) {
				marked[i] = true;
				pri = v[i].first;
				--n;
				if (n == 0 && pri == ult) {
					fin = true;
				}
				else {
					resuelve(v, marked);
					++n;
					marked[i] = false;
					pri = v[i].second;
				}
			}

		}
	}
}


int main()
{
	cin >> n;
	while (n!=0) {
		cin >> m;
		fin = false;
		vector<pair<int, int>> v(m);
		vector<bool> marked(m, false);
		int aux;
		cin >> pri >> pri >> ult >> aux;
		for (int i = 0; i < m; ++i) {
			cin >> v[i].first >> v[i].second;
		}
		if (n == 0) {
			if (pri == ult) cout << "YES\n";
		}
		else resuelve(v, marked);
		if (fin) cout << "YES\n";
		else cout << "NO\n";
		cin >> n;
	}
	return 0;
}