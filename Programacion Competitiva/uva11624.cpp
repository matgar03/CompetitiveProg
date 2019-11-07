#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
int n,c,f;

int df[]={1,0,-1,0};
int dc[]= {0,1,0,-1};

bool ok(int i,int j,const vector<vector<char>> &m){
    return (i>=0 && j>=0 && i < f && j< c);
}

void solucion(vector<vector<char>> &m,vector<pair<int,int>>&conjfire,vector<pair<int,int>>&conjj ){
   
    int contf=0,contj=0,aux2,cont=0;
   
    bool fin =false, puede = true;
    if(conjj[contj].first==f-1 || conjj[contj].second==c-1 || conjj[contj].first==0 || conjj[contj].second==0){
        cout << 1 << "\n";
        return;
    }
    while(!fin && puede){
        aux2=conjfire.size();
        for (;contf<aux2;++contf){
            for(int i=0;i<4;++i){
                if (ok(conjfire[contf].first+df[i],conjfire[contf].second+dc[i],m) && (m[conjfire[contf].first+df[i]][conjfire[contf].second+dc[i]] == 'J' || m[conjfire[contf].first+df[i]][conjfire[contf].second+dc[i]] == '.')) {
                    m[conjfire[contf].first+df[i]][conjfire[contf].second+dc[i]] = 'F';
                    conjfire.push_back(pair<int,int> (conjfire[contf].first+df[i],conjfire[contf].second+dc[i]));
                }
            }
        }
        puede = false;
        ++cont;
        aux2=conjj.size();
        for (;contj<aux2;++contj){
            for(int i=0;i<4;++i){
                if (ok(conjj[contj].first+df[i],conjj[contj].second+dc[i],m) && (m[conjj[contj].first+df[i]][conjj[contj].second+dc[i]] == '.')) {
                    puede=true;
                    m[conjj[contj].first+df[i]][conjj[contj].second+dc[i]] = 'J';
                    conjj.push_back(pair<int,int> (conjj[contj].first+df[i],conjj[contj].second+dc[i]));
                    if (conjj[contj].first+df[i]==0||conjj[contj].first+df[i]==f-1||conjj[contj].second+dc[i]==0||conjj[contj].second+dc[i]==c-1)fin=true;
                }
            }
        }
    }
    if (fin) cout<<cont+1<<'\n';
    else cout <<"IMPOSSIBLE\n";

}

int main(){
    cin>>n;
    while(n--){
        cin>>f>>c;
        vector<vector<char>> m(f,vector<char>(c));
        vector<pair<int,int>> conjfire,conjj;
        for (int i=0;i<f;++i){
            for(int j=0;j<c;++j) {
                cin >> m[i][j];
                if (m[i][j]=='F'){
                    conjfire.push_back(pair<int,int> (i,j));
                }
                else if (m[i][j]=='J'){
                    conjj.push_back(pair<int,int> (i,j));
                }
            }
        }
        solucion(m,conjfire,conjj);
    }
    return 0;
}