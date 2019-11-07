#include <iostream>
#include <vector>
#include <queue>


using namespace std;
using vii = vector<int>;

int n;
int e;



void solucion(){
    vector<vii> adj(n);
    cin >> e;
    for(int i = 0 ;  i < e;++i){
        int a1,a2;
        cin >> a1 >> a2;
        adj[a1].push_back(a2);
        adj[a2].push_back(a1);
    }
    queue<int> q;
    vector <int>col(n,0);
    int color;
    bool peta = false;
    q.push(0);
    col[0]=1;
    while(!q.empty() && !peta){
        int v= q.front();q.pop();
        color= -col[v];
        for(int w : adj[v]){
            if(col[w]== 0){
                col[w]=color;
                q.push(w);
            }
            else if(col[w]!= color){
                peta=true;
            }
        }
    }
    if(peta) cout << "NOT BICOLORABLE.\n";
    else cout << "BICOLORABLE.\n";

}

int main(){
    cin >> n;
    while(n!= 0){
        solucion();
        cin >> n;
    }

    return 0;
}