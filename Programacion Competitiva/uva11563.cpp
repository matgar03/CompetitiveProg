#include <iostream>
#include <vector>
#include <set>

using namespace std;

int c,n,a,cont;


int main(){
    while (cin>>c>>n>>a){
        cont=0;
        vector<int> accesos(a),aux(n,0),next(n,200000);
        for (int i=0;i<a;++i){
            cin>>accesos[i];            
            if (aux[accesos[i]!=0]){
                next[aux[accesos[i]]]=i;
            }
            aux[accesos[i]]=i;
        }
        aux=vector<int> (n,-1);
        set<pair<int,int>> cache;
        for (int i=0;i<a;++i){
            if (aux[accesos[i]]!=-1){
                cache.erase({aux[accesos[i]],accesos[i]});
                
            }
            else if (cache.size()<c){
                ++cont;
            }
            else{
                ++cont;
                aux[(--cache.end())->second]=-1;
                cache.erase(--cache.end());

            }
            cache.insert({next[i],accesos[i]});
            aux[accesos[i]]=i;
        }
        cout<<cont<<'\n';

    }
    return 0;
}