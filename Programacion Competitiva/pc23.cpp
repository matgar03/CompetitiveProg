#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
int N,S,T,P;

void dijkstra(int s, vector<int> & dist,const vector<vector<pair<int, int>>> &v) {
	dist[s] = 0;
	
	priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, s });
	while (!pq.empty()) {
		pair<int, int> front = pq.top(); pq.pop();
		int d = front.first, u = front.second;
		if (d > dist[u]) continue;
		for (auto a : v[u]) {
			if (dist[u] < INT_MAX && dist[u] + a.first < dist[a.second]) {
				dist[a.second] = dist[u] + a.first;
				pq.push({ dist[a.second], a.second });
			}
		}
	}
}

void solucion(){
    vector<vector<pair<int,int>>> m(N+1);
    for(int i = 0 ; i < P; ++i){
        int a,b,val;
        cin >> a  >> b >> val;
        m[b].push_back(pair<int,int>(val,a));
    }
	vector<int> dist(N+1, INT_MAX);
    dijkstra(S,dist,m);
    int sol = 0;
    for(int i = 1; i <N+1;++i){
        if(i==S)continue;
        if(dist[i]<= T )++sol;
    }
    cout << sol << '\n';
}

int main(){
    while(cin >> N >> S >> T >> P){
        solucion();
    }
    
    return 0;

}