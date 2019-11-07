#include <iostream>
#include <vector>
#include <string>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
bool ciclo;

/*
int dfs(int v, vector<bool> &visited, vvi &adjList) {
	int tam = 1; visited[v] = true;
	for (int w : adjList[v])
		if (!visited[w]) tam += dfs(w,visited,adjList);
	return tam;
}*/

void dfs2(int u, vi &estado, vvi &adj) {
	estado[u] = 1;
	for (int i = 0; i < adj[u].size(); ++i) {
		int v = adj[u][i];
		if (estado[v] == 1){
            ciclo = true;
            estado[v]=2;
        }
			
		else if (estado[v]==0) dfs2(v, estado, adj);
			
	}
	estado[u] = 2;
	//return false;
}


void solucion() {
	int l;
	cin >> l;
	vector <vector<int>> v(l + 1);
	for (int i = 0; i < l; ++i) {
		char c;
		cin >> c;
		if (c != 'A') {
			int s;
			cin >> s;
			v[i].push_back(s-1);
		}
		if (c != 'J') {
			v[i].push_back(i + 1);
		}
	}
	vector<int> estado(l + 1,0);
	vector<bool> visited(l+1, false);
	bool fin = false;
	//dfs(0, visited, v);
	//if (visited[l])fin = true;
	dfs2(0, estado, v);
	if (!estado[l]) {
		cout << "NEVER\n";
	}
	else if (!ciclo) {
		cout << "ALWAYS\n";
	}
	else {
		cout << "SOMETIMES\n";
	}


}


int main() {
	int n;
	cin >> n;
	while (n--) {
		ciclo=false;
		solucion();
	}
	return 0;
}