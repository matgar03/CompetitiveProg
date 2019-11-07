#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

int f,c;



void solucion(){
    cin >> f >> c;
    pair<int,int> ini;
    cin >> ini.first >> ini.second;
    int beep;
    cin >> beep;
    vector<pair<int,int>> v(beep);

    for(int i = 0; i < beep;++i){
        cin >> v[i].first >> v[i].second;
    }

    vector<vector<int>> dist(beep+1,vector<int>(beep+1));
    dist[0][0]=0;
    for(int i= 0; i < beep;++i){
        dist[0][i+1]=abs(ini.first-v[i].first)+ abs(ini.second-v[i].second);
        dist[i+1][0]=dist[0][i+1];
    }
    for(int i = 1 ;i <= beep;++i){
        dist[i][i]=0;
        for(int j = i+1;j <= beep;++j){
            dist[i][j]=abs(v[i-1].first-v[j-1].first)+ abs(v[i-1].second-v[j-1].second);
            dist[j][i]= dist[i][j];
        }
    }
 /*   for(int i = 0; i <beep+1;++i){
        for(int j = 0; j< beep+1;++j){
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }*/

    int total= pow(2,beep);

    vector<vector<int>> c(total,vector<int>(beep,0));

    for(int i = 0 ; i < total; ++i){
        for(int j = 0 ;j < beep;++j){
            if(i & (1<<j)){
                int aux= i ^ (1<<j) ;
                int sol= INT_MAX;
                for(int k=0;k < beep;++k ){
                    if(k==j)continue;
                    if(aux & (1<<k)){
                        sol=min(sol,c[aux][k]-dist[0][k+1]+dist[k+1][j+1]+dist[j+1][0]);
                    }
                }
                if(sol == INT_MAX)sol= 2*dist[0][j+1];
                c[i][j]= sol;
            }
        }
    } 

    int res=INT_MAX;
    for(int i = 0 ; i < beep;++i){
        res=min(res,c[total-1][i]);
    }
    cout << "The shortest path has length " << res << '\n';

}

int main(){
    int n;
    cin >> n;
    while(n--){
        solucion();
    }
    return 0;
}