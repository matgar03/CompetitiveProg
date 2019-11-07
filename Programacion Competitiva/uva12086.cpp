#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N;
int casos;

class FenwickTree{
    vector<int> ft;
    public:
        FenwickTree(int n) { ft.assign(n+1, 0); }

        int getSum(int b) {
            int ret = 0;
            while (b) {
                ret += ft[b]; b -= (b & -b);
            }
            return ret;
        }

        void add(int pos, int val) {
            while (pos < ft.size()) {
                ft[pos] += val; pos += (pos & -pos);
            }
        }

        int getSum(int a, int b) {
            return getSum(b) - getSum(a - 1);
        }
        int getValue(int pos) {
            return getSum(pos) - getSum(pos - 1);
        }

        void setValue(int pos, int val) {
            add(pos, val - getValue(pos));
        }   
};

void solucion(){
    FenwickTree feny(N); int val;

    for(int i = 1 ; i < N+1 ;++i){
        cin >> val;
        feny.add(i,val);
    }
    cout << "Case " << casos << ":\n";
    string s;
    cin >> s;
    int v1,v2;
    while(s != "END"){
        cin >> v1 >> v2;
        if(s == "S"){
            feny.setValue(v1,v2);
        }
        else{
            cout << feny.getSum(v1,v2) << '\n';
        }

        cin >> s;
    }
    
}

int main(){
    
    cin >> N;
    casos = 1;
    while(N!= 0){
        solucion();
        cout << '\n';
        cin >> N;
        ++casos;
    }

    return 0;
}