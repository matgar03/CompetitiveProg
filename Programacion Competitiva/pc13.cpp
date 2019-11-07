#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int p,s;

void solucion(){
    vector<int> v(s);
    for(int i = 0 ; i < s; ++i){
        cin >> v[i];
    }
    vector<vector<int>>m(p+1,vector<int>(s,INT_MAX));

    for(int j = 0; j < s;++j)m[0][j]=0;

    for(int j = 0; j < s;++j){
        for(int i = 1; i<= p;++i){
            int sol= INT_MAX;
            if(j> 0) sol=min(sol,m[i][j-1]);
            for(int k = 1;k*v[j] <= i;++k){
                int aux = m[i-k*v[j]][j];
                if (aux != INT_MAX) sol = min(sol,aux + k);
            }
            m[i][j]= sol;
        }
    }
    

    if(m[p][s-1] == INT_MAX) {
        cout << "Imposible\n";
        return;
    }
    int cont = p;
    int d = s-1;
    vector<int> res;
    while(cont > 0){
        if((cont -v[d]) >= 0 && (m[cont-v[d]][d] + 1) ==  m[cont][d]){
            res.push_back(v[d]);
            cont -= v[d];
        }
        else --d;
    }
    cout << m[p][s-1] << ":";
    for(int u = 0 ; u <res.size();++u){
        cout << ' ' << res[u];
    }
    cout << '\n';
    
}


int main(){
    while(cin >> p >> s){
        solucion();
    }

    return 0;
}