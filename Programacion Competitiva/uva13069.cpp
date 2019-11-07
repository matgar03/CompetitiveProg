#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int i,f;


void solucion(){
    vector<int> v(10000,-1);
    queue<int> q;
    q.push(i);
    v[i]=0;
    while(!q.empty()){
        int a=q.front();q.pop();
        if (v[(a+1)%10000]==-1){
            v[(a+1)%10000]=v[a]+1;
            if ((a+1)%10000==f)break;
            q.push((a+1)%10000);
        }
        if (v[(a*2)%10000]==-1){
            v[(a*2)%10000]=v[a]+1;
            if ((a*2)%10000==f)break;
            q.push((a*2)%10000);
        }
        if (v[(a/3)%10000]==-1){
            v[(a/3)%10000]=v[a]+1;
            if ((a/3)%10000==f)break;
            q.push((a/3)%10000);
        }
    }
    cout<<v[f]<<'\n';


}

int main(){
    while(cin>> i  >> f){

        solucion();
    }
    return 0;
}