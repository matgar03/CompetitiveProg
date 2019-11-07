#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#include <iomanip>

using namespace std;
int a, b,cas;



void floyd(vector<vector<int>> &adjMat) {
    for (int k = 0; k < 101; k++)
        for (int i = 0; i < 101; i++)
            for (int j = 0; j < 101; j++)
                if (adjMat[i][k]+adjMat[k][j]<adjMat[i][j]){
                adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
            }
}





int main(){
    cin >> a >> b;
    cout << fixed << setprecision(3);
    cas=0;
    while(a!= 0 || b != 0){
        set<int> aux;
        ++cas;
        vector<vector<int>> v(101,vector<int>(101,10000));
        while(a!= 0 ||b != 0){
            aux.insert(a);
            aux.insert(b);
            v[a][b]=1;      
        cin>>a>>b;
        }
        for(int i = 0 ; i  < 101; ++i){
            v[i][i]=0;
        }
        floyd(v);
        double tot=0,au=aux.size();
        for (int i=1;i<101;++i){
        for (int j=1;j<101;++j) if (v[i][j]!=10000)tot+=v[i][j];
        }
        
        double med=tot/(au*(au-1));
        cout<<"Case "<<cas<<": average length between pages = "<<med<<" clicks\n";
        cin>>a>>b;
    }
   
    return 0;
}