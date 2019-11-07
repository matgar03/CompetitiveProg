#include <iostream>
#include <vector>

using namespace std;
int N,K;


class SegmentTree {
    
    int tam; 
    public:
    vector<int> st;
    SegmentTree(int maxN) {
        st.reserve(4 * maxN + 10);
    }
    
    int query(int a, int b) {
        return query(1, 0, tam-1, a, b);
    }

    int query(int vertex, int L, int R, int i, int j) {
        if (i > R || j < L) {
            return 1;
        }
        if (L >= i && R <= j)  return st[vertex];
        int mitad = (L + R) / 2;
        return query(2*vertex, L, mitad, i, j) * query(2*vertex+1, mitad+1, R, i, j);
    }

    void update(int pos, int newVal) {
        update(1, 0, tam-1, pos, newVal);
    }

    void update(int vertex, int l, int r, int pos, int newVal) {
        if ((pos < l) || (r < pos)) return;
        if (l == r) {
            st[vertex] = newVal;
            return;
        }

        int m = (l+r) / 2;
        if ((l <= pos) && (pos <= m))
            update(2 * vertex, l, m, pos, newVal);
        else
            update(2 * vertex + 1, m+1, r, pos, newVal);
        st[vertex] = st[2*vertex] * st[2*vertex + 1];
    }

    void build(int *values, int n) {
        tam = n;
        build(values, 1, 0, n-1);
    }

    void build(int *values, int p, int l, int r) {
        if (l == r) {
            st[p] = values[l];
            return;
        }
        int m = (l+r)/2;
        build(values, 2*p, l, m);
        build(values, 2*p+1, m+1, r);
        st[p] = st[2*p]*st[2*p+1];
    }
   
};

void solucion(){
    SegmentTree seg(N);
    int aux;
    int v[N];
    for(int i = 0 ; i < N; ++i){        
        cin >> aux;
        if(aux > 0) v[i]= 1;
        else if(aux == 0) v[i]= aux;
        else v[i]= -1;
    }
    seg.build(v,N);

    string s;int a1,a2;
    for(int  i = 0 ; i < K;++i){
        cin >> s >> a1 >> a2;
        --a1;
        if (s=="P"){
            --a2;
            aux=seg.query(a1,a2);
            if (aux==0)cout<<'0';
            else if (aux<0)cout<<'-';
            else cout<<'+';
        }
        else {
            if (a2>0) seg.update(a1,1);
            else if (a2<0) seg.update(a1,-1);
            else seg.update(a1,0);
        }
    }
    cout<<'\n';
}

int main(){
    while(cin >> N >> K){
        solucion();
    }
    return 0;
}