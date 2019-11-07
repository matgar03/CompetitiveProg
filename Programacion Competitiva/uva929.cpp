#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;
int df[]={1,0,-1,0};
int dc[]= {0,1,0,-1};
int f,c;
struct iival{
    int val;
    int row;
    int col;
};

bool operator >(const iival & i1,const iival & i2){
   if(i1.val== i2.val) return i1.col+i1.row > i2.col + i2.row;
   return i1.val>i2.val;
}

bool ok(int i,int j){
    return (i>=0 && j >= 0 && i<f && j<c);
}

void solucion(){
    
    cin>> f >> c;
    vector<vector<int>> m(f,vector<int>(c));
    for(int i = 0 ; i < f; ++i){
        for(int j = 0 ; j< c; ++j){
            cin>>m[i][j];
        }
    }
    vector<vector<int>> spt(f,vector<int>(c,INT_MAX));
    spt[0][0]=m[0][0];
    priority_queue <iival,vector<iival>,greater<iival>> pq;
    iival cas;
    cas.val=spt[0][0];
    cas.row= 0;
    cas.col=0;
    pq.push(cas);
    while(!pq.empty()){
        iival front = pq.top();
        pq.pop();
        int a,b;
        a=front.row;
        b=front.col;
        if(front.val > spt[a][b])continue;
        for(int i = 0 ;i < 4;++i){
            if(ok(a+df[i],b+dc[i]) && spt[a][b] + m[a+df[i]][b+dc[i]] < spt[a+df[i]][b+dc[i]]){
              spt[a+df[i]][b+dc[i]]=  spt[a][b] + m[a+df[i]][b+dc[i]];
              cas.val=spt[a+df[i]][b+dc[i]];
              cas.row= a+df[i];
              cas.col= b+dc[i];
              pq.push(cas);
            }
        }
    }

    cout << spt[f-1][c-1]<< '\n';
}

int main(){
    int n;
    cin >> n;
    while(n--){
        solucion();
    }
    return 0;
}