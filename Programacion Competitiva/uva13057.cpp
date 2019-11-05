#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
int casos;

struct SCC{
    int n;
    vvi adj,adj_t,components,adj_condensation;
    vector<int> order,component;
    vector<bool> vis;

    SCC(int n) : n(n){
        adj.resize(n);
        adj_t.resize(n);
    }

    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj_t[v].push_back(u);
    }

    void dfs1(int v){
        vis[v] = true;
        for(int u : adj[v]){
            if(!vis[u])dfs1(u);
        }
        order.push_back(v);
    }

    void dfs2(int v, int c){
        vis[v] = true;
        components.back().push_back(v);
        component[v]= c;
        for(int u : adj_t[v]){
            if(!vis[u])dfs2(u,c);
        }
    }

    int solve(){
        vis.assign(n,false);
        for(int i = 0 ; i < n; ++i){
            if(!vis[i])dfs1(i);
        }
        vis.assign(n,false);
        reverse(order.begin(), order.end());
        components.clear();
        component.resize(n);
        int c = 0;
        for(int i: order){
            if(!vis[i]){
                components.push_back({});
                dfs2(i,c);
                ++c;
            }
        }
        adj_condensation.resize(c);
        for(int k = 0 ; k < n;++k){
            for(int u : adj[k]){
                if(component[k] != component[u]){
                    adj_condensation[component[k]].push_back(component[u]);
                }
            }
        }
        return c;
    }

};
void solucion(){
    int v,a;
    cin >> v >> a;
    SCC g(v);
    for(int i =0 ; i < a;++i){
        int aux1, aux2;
        cin >> aux1 >> aux2;
        --aux1;--aux2;
        g.addEdge(aux1,aux2);
    }
  
    int tam = g.solve();
   
    vi sol(tam,0);int cont=0;

    for(int i = 0; i <tam;++i){
        for(int k : g.adj_condensation[i]){
            ++sol[k];   
        }
    }
   
    for(int i = 0; i < tam;++i){
        if(sol[i]== 0)++cont;
    }
    cout << "Case " << casos << ": " << cont << '\n' ;

}

int main(){
    int n;
    cin >> n;
    casos=1;
    while(n--){
        solucion();
        casos++;
    }

    return 0;
}