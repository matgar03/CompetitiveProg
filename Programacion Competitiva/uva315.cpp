#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>


using namespace std;
int n, cont,dfsRoot;

void dfs(int u,int uParent,const vector<vector<int>> & g,vector<int>&horaVertice, vector<int> &alcanzable, int &hora, int & hijosRaiz, vector<bool> &sol){
    horaVertice[u]=hora;
    alcanzable[u]=hora;
    ++hora;
    for(int i = 0 ; i < g[u].size();++i){
        int v= g[u][i];
        if(v == uParent) continue;
        if(horaVertice[v] == 0){
            if(u==dfsRoot) hijosRaiz++;
            dfs(v,u,g, horaVertice,alcanzable,hora,hijosRaiz, sol);
            if(alcanzable[v]>= horaVertice[u]){
                if(uParent != 0 ){
                    sol[u]=true;
                }
            }
            alcanzable[u]= min(alcanzable[u], alcanzable[v]);
        } 
        else {
            alcanzable[u]= min(alcanzable[u], horaVertice[v]);
        }
        
    }
}

void solucion(){
    vector<bool> sol(n+1,false);
    vector<vector<int>> g(n+1);
    int c;
    char car;
    cin.get(car);
    string s;
    getline(cin,s);
    stringstream aux(s);
    aux >> c;
    while(c != 0){
        int a;
       
        while(aux >> a){
            g[c].push_back(a);
            g[a].push_back(c);
        }
        getline(cin,s);
        stringstream aux(s);
        aux >> c;
    }
    vector<int> horaVertice(n+1,0);
    vector<int> alcanzable(n+1, -1);
    int hora = 1;
    int hijosRaiz; cont =0;
    for (int i=1; i<=n; ++i){
        if (horaVertice[i]== 0){
            hijosRaiz=0;dfsRoot=i;
            dfs(i,0,g, horaVertice,alcanzable,hora,hijosRaiz,sol);
            if (hijosRaiz>1)sol[i]=true;
        }

    }
    for (int i=1;i<sol.size();++i)
        if (sol[i])cout << "g ";
        else cout << "m ";
    cout<<cont<<'\n';
}

int main(){
    cin >> n ;
    while(n!= 0){
        solucion();
        cin >> n ;
    }
}