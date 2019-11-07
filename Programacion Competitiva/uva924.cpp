#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;
int e;

using vvi= vector<vector<int>>;

void bfs(const int s, const vvi & v, vector<int> & dis){
    queue<int> q;
    dis[s]=0;
    vector<bool> vis(e,false);
    vis[s]=true;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int w : v[u]){
            if(!vis[w]){
                dis[w]=dis[u]+1;
                vis[w]=true;
                q.push(w);
            }
        }
    }
}


void solucion(){
    vvi v(e);
    for(int i = 0 ; i < e;++i){
        int cant;
        cin >>cant;
        while(cant--){
            int emp;
            cin >> emp;
            v[i].push_back(emp);
        }
    }
    
    int test;
    cin >> test;

    while(test--){
        int s;
        cin >> s;
        vector<int> dis(e,INT_MAX);
        bfs(s,v,dis);
        sort(dis.begin(),dis.end());
        int ac= 0;
        int cont = 1;
        int max= 0;
        int dmax= 0;
        if(e >1 && dis[1]!= INT_MAX){
            ac=1;
            cont=1;
            for(int i = 2; i < e;++i){
                if(dis[i]== INT_MAX) break;
                if(dis[i]!= ac){
                    if(cont> max){
                        max=cont;
                        dmax=ac;
                    }
                    ac= dis[i];
                    cont=1;
                }
                else{
                    ++cont;
                }
            }
            if(cont> max){
                    max=cont;
                    dmax=ac;
            }
            cout << max << ' ' << dmax << '\n';
        }
        else cout << 0<< '\n';
    }
    
}

int main(){
    while(cin >> e){
        solucion();
    }
    return 0;
}
