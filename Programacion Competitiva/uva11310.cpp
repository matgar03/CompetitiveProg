#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long int> sol (41,-1);

void init(){
    sol[0] = 1;
    sol[1]=1;
    sol[2]= sol[1]+ 4*sol[0];
    for(int i = 3; i < 41; ++i){
        sol[i]= sol[i-1]+4 *sol[i-2]+ 2*sol[i-3];
    }

}

int main(){
    int n;int t;


    cin >> n;

    init();



    for(int i = 0; i < n; ++i){
        cin >> t;
        cout << sol[t] << '\n';
    }

    return 0;
}