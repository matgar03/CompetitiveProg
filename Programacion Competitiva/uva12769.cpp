#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N;

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
        int getValue(int a) {
            return getSum(a);
        }

        void setValue(int pos, int val) {
            add(pos, val - getValue(pos));
        }   

        void add(int a, int b, int val){
            add(a,val) ; add(b, val-1);
        }

};


void solucion(){
    FenwickTree feny(100000);
    char c;
    int a1,a2,a3;
    while(N--){
        cin >> c;
        if(c == 'B'){
            cin >> a1 >> a2 >> a3;
            feny.add(a1,a2,a3);
        }
        else{
            cin >> a1;
            cout << feny.getValue(a1) << '\n';
        }
        
    }
}

int main(){
    cin >> N;
    while(N){
        solucion();
        cin >> N;
    }

    return 0;
}