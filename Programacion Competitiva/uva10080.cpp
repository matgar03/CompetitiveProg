#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using vvi =  vector<vector<int>>;
int g, h, t, v;


vector<int> match, vis;
int aug(int l,const vvi & m) { // Devuelve 1 si encuentra un augmenting path para el matching M representado en match.
   if (vis[l]) return 0;
   vis[l] = 1;
   for (auto r : m[l]) {
      if (match[r] == -1 || aug(match[r],m)) {
         match[r] = l;
         return 1;
      }
   }
   return 0;
}



void solucion(){
    vvi m(g+h);
    vector <pair<double,double>> cord(g+h);
    for(int i = 0;i<g+h;++i ){
        cin >> cord[i].first >> cord[i].second;
    }
    double dist = 1.0*t*v; 

    for(int i =0; i < g; ++i){
        for(int j = g; j < g+h;++j){
            double eso= sqrt(((cord[i].first-cord[j].first)* (cord[i].first-cord[j].first)) + ((cord[i].second-cord[j].second)* (cord[i].second-cord[j].second)));
            if(eso <= dist){
                m[i].push_back(j);
                m[j].push_back(i);
            }
        }
    }
    int mcbm = 0;
    match.assign(g + h, -1);
    for (int l = 0; l < g; l++) {
        vis.assign(g, 0);
        mcbm += aug(l,m);
   }
   cout << g - mcbm << '\n';
}


int main(){

    while(cin >> g >> h >> t >> v){
        solucion();
    }
    return 0;
    
}