#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iomanip>


using namespace std;

int n, m, cont, numcase;


void scc(int u, vector<int> &horaVertice, vector<int> &alcanzable, vector<int> &sccstack,vector<bool> &incurrentscc, int &hora, vector<vector<int>> &vec, vector <vector<string>>&sol, unordered_map<int,string> &mapa) {
	horaVertice[u] = alcanzable[u] = hora;
	hora++;
	incurrentscc[u] = true;
	sccstack.push_back(u);
	for (int i = 0; i < vec[u].size(); ++i) {
		int v = vec[u][i];
		if (!horaVertice[v])
			scc(v, horaVertice, alcanzable, sccstack, incurrentscc, hora, vec,sol,mapa);
		if (incurrentscc[v])
			alcanzable[u] = min(alcanzable[u], alcanzable[v]);
	}
	if (horaVertice[u] == alcanzable[u]) {
		vector<string> sc;
		int v;
		do {
			v = sccstack.back();
			sccstack.pop_back();
			sc.push_back(mapa[v]);
			incurrentscc[v] = false;
		} while (u != v);
		sort(sc.begin(), sc.end());
		sol.push_back(sc);
	}
}

int main() {
	cin >> n >> m;
	numcase = 1;
	while (n != 0 || m != 0) {
		vector <vector<string>> sol;
		unordered_map<string, int> mapa1;
		unordered_map<int, string> mapa2;
		vector<vector<int>> v(n);
		cont = 0;
		string s1,s2;
		for (int i=0;i<m;++i) {
			cin >> s1 >> s2;
			if (!mapa1.count(s1)) {
				mapa1[s1] = cont;
				mapa2[cont] = s1;
				++cont;
			}
			if (!mapa1.count(s2)) {
				mapa1[s2] = cont;
				mapa2[cont] = s2;
				++cont;
			}
			v[mapa1[s1]].push_back(mapa1[s2]);
		}

		vector<int> horaVertice(n, 0);
		vector<int> alcanzable(n, 0);
		vector<int> sccstack;
		vector<bool> incurrentscc(n, false);
		int hora = 1;
		for (int i = 0; i < n; ++i) {
			if (!horaVertice[i])
				scc(i,horaVertice,alcanzable,sccstack,incurrentscc,hora,v,sol,mapa2);
		}
		vector<pair<string, int>> orden(sol.size());
		for (int i = 0; i < sol.size(); ++i) {
			orden[i] = (pair<string,int>(sol[i][0],i));
		}
		sort(orden.begin(), orden.end());
		cout << "Calling circles for data set " << numcase << ":\n";
		for (int i = 0; i < sol.size(); ++i) {
			for (int j = 0; j < sol[orden[i].second].size()-1; ++j) {
				cout << sol[orden[i].second][j] << ", ";
			}
			cout<< sol[orden[i].second][sol[orden[i].second].size()-1] << '\n';
		}
		cout << '\n';
		cin >> n >> m;
		++numcase;
	}
	return 0;
}
