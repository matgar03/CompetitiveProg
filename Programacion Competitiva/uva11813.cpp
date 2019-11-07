#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
using ii = pair<int,int>;
using vii = vector<ii>;

void dijkstra(int s, vector<int> &dist, const vector<vector<pair<int,int>>> & v) {
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;
        for (auto a : v[u]) {
            if (dist[u]  < dist[a.second]-a.first ) {
                dist[a.second] = dist[u] + a.first;
                pq.push({dist[a.second], a.second});
            }
        }
    }
}

void solucion(){
    int ver,ar;
    cin >> ver >> ar;
    
    vector <vector<pair<int,int>>> v(ver);

    for(int i = 0 ; i < ar;++i){
        int a1,a2,a3;
        cin >> a1 >> a2  >> a3;
        v[a1].push_back(pair<int,int>(a3,a2));
        v[a2].push_back(pair<int,int>(a3,a1));
    }

    int s;
    cin >> s;
    vector<int> g(s);
    
    for(int i = 0 ; i<s;++i){
        cin >> g[i];
    }
    
    vector<vector<int>> m(s+1,vector<int>(s+1));
    vector<int> dist(ver,INT_MAX);
    dijkstra(0,dist,v);
    m[0][0]=0;
    for(int i = 1 ; i <=s;++i ){
        m[0][i]= dist[g[i-1]];
        m[i][0]= m[0][i];
    }

    for(int i = 1; i<=s;++i){
        vector<int> dist(ver,INT_MAX);
        dijkstra(g[i-1],dist,v);
        for(int j = 1 ; j <=s;++j ){
            m[i][j]= dist[g[j-1]];
        }
    }
    
    int total= (1<<s);

    /*for(int i = 0 ; i <s+1;++i){
        for(int j = 0; j < s+1;++j){
            cout << m[i][j] << ' ';
        }
        cout << '\n';
    }*/
    
    vector<vector<int>> sol(total,vector<int>(s));

    for(int i = 0 ; i <total; ++i){
        for(int j = 0; j<s;++j){
            if(i & (1<<j)){
                int aux = i ^ (1 <<j);
                int wer=INT_MAX;
                for(int k = 0; k<s;++k){
                    if(k == j)continue;
                    if(aux & (1<<k)){
                        wer = min(wer, sol[aux][k]- m[k+1][0] + m[k+1][j+1] + m[j+1][0]);
                    }
                }
                if(wer ==INT_MAX) wer = 2 *m[j+1][0];
                sol[i][j] = wer;
            }
        }
    }

    /* for(int i = 0 ; i <total;++i){
        for(int j = 0; j < s;++j){
            cout << sol[i][j] << ' ';
        }
        cout << '\n';
    }*/

    int res= INT_MAX;
    for(int i = 0;i <s; ++i){
        res= min(res,sol[total-1][i]);
    }

    cout << res <<'\n';

}

int  main(){
    int n;
    cin >> n;
    while(n--){
        solucion();
    }
    return 0 ;
}