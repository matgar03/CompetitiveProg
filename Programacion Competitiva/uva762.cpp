#include <iostream>
#include <vector>
#include <string>
#include <queue>


using namespace std;
using vii = vector<int>;

int n;

int esta(const string & s , const vector<string> & d){
    for(int i = 0 ; i < d.size();++i){
        if(d[i] == s )return i;
    }
    return -1;
}


void solucion(){
    vector<vii> adj; vector <string>  dic;
    string aux; int cont = 0;
    vii vacio;
    for(int i = 0; i < n;++i){
        cin >> aux;
        int v1 = esta(aux,dic);
        if(v1 == -1){
            v1= cont;
            ++cont;
            dic.push_back(aux);
            adj.push_back(vacio);
        }
        cin >> aux;
        int v2 = esta(aux,dic);
        if(v2 == -1){
            v2= cont;
            ++cont;
            dic.push_back(aux);
            adj.push_back(vacio);
        }
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }

    string a1,a2;
    vii sol(cont);
   
    cin >> a1 >> a2;
    int ori,fin;
    ori = esta(a1,dic);
    fin = esta(a2,dic);
    if(ori == -1 || fin == -1){
        cout << "No route\n\n";
        
        return;
    }
    queue<int> q;
    vector <bool>vis(cont);
    vis[ori]= true;
    q.push(ori);
    bool final=false;
    while(!q.empty() && !final){
        int v= q.front();q.pop();
        for(int w : adj[v]){
            if(!vis[w]){
                vis[w]=true;
                q.push(w);
                sol[w]=v;
                if(w == fin) {
                    final=true;
                    break;
                    }
            }
        }
    }

    if(!vis[fin]){
        cout << "No route\n\n";
        
        return;
    }
    vector <string> lq; 
    int x=sol[fin];
    while(x!= ori){
        lq.push_back(dic[x]);
        x=sol[x];
    }
    cout << dic[ori]<< ' ';
    for(int i = lq.size()-1;i >= 0; --i ){
        cout << lq[i] << '\n' << lq[i] << ' ' ;
    }
    cout << dic[fin] << "\n\n";
}

int main(){
    while(cin >> n){
        solucion();
    }

    return 0;
}