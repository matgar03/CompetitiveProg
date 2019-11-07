#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int x,y;

int df[] = {1,0,-1,0}, dc[] = {0,1,0,-1};
struct tipo{
    int numero;
    char letra;
};

bool operator <(const tipo &p1, const tipo &p2){
    if (p1.numero==p2.numero) return p2.letra<p1.letra;
    return p1.numero < p2.numero;
}

bool ok(int i, int j) {
    return 0 <= i && i < x && 0 <= j && j < y;
}

int dfs(int i, int j, vector<vector<bool>> &visited, const vector<vector<char>> &m,const char &bus) {
    int tam = 1; visited[i][j] = true;
    for (int k = 0; k < 4; ++k) {
        int ni = i + df[k], nj = j + dc[k];
        if (ok(ni,nj)&&m[ni][nj]==bus&&!visited[ni][nj])
        tam += dfs(ni, nj, visited,m,bus);
    }
    return tam;
}


void solucion(){
    vector<vector<char>> m(x,vector<char>(y));
    vector<vector<bool>> visited(x,vector<bool>(y,false));
    vector<tipo> sol;
    char aux;
    for (int i=0; i<x;++i){
        for (int j=0;j<y;++j) cin.get(m[i][j]);
        cin.get(aux);
    }
    tipo t;
    for(int i = 0; i < x; ++i){
        for (int j = 0; j < y; ++j){
            if (!visited[i][j] && m[i][j] != '.') {
                t.letra= m[i][j];
                t.numero = dfs(i,j,visited,m,t.letra);
                sol.push_back(t);
            }
        }
    }
    sort(sol.begin(), sol.end());
    cout << "Problem " << n << ":\n";
    for(int i = sol.size()-1 ; i >= 0;--i){
        cout << sol[i].letra << ' ' << sol[i].numero << '\n';
    }
}

int main(){
    n=1;
    cin>> x >> y;
    char aux;

    while(x!= 0 && y!= 0){
        cin.get(aux);
        solucion();
        ++n;
        cin>> x >> y;
    }

    return 0;
}