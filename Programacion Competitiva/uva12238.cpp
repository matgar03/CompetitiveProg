#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = 1000000002;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvii = vector<vii>;



int N;

/*
class SegmentTree {

	int tam;
	vector<int> st;
public:
	SegmentTree(int maxN) {
		st.assign(4 * maxN + 10,INF);
	}

	int query(int a, int b) {
		return query(1, 0, tam - 1, a, b);
	}

	int query(int vertex, int L, int R, int i, int j) {
		if (i > R || j < L) {
			return INF;
		}
		if (L >= i && R <= j) {
			return vertex;
		}
		int mitad = (L + R) / 2;
		return min(query(2 * vertex, L, mitad, i, j), query(2 * vertex + 1, mitad + 1, R, i, j));
	}

	void update(int pos, int newVal) {
		update(1, 0, tam - 1, pos, newVal);
	}

	void update(int vertex, int l, int r, int pos, int newVal) {
		if ((pos < l) || (r < pos)) return;
		if (l == r) {
			st[vertex] = newVal;
			return;
		}

		int m = (l + r) / 2;
		if ((l <= pos) && (pos <= m))
			update(2 * vertex, l, m, pos, newVal);
		else
			update(2 * vertex + 1, m + 1, r, pos, newVal);
		st[vertex] = min(st[2 * vertex], st[2 * vertex + 1]);
	}

	void build(int* values, int n) {
		tam = n;
		build(values, 1, 0, n - 1);
	}

	void build(int* values, int p, int l, int r) {
		if (l == r) {
			st[p] = values[l];
			return;
		}
		int m = (l + r) / 2;
		build(values, 2 * p, l, m);
		build(values, 2 * p + 1, m + 1, r);
		st[p] = min(st[2 * p], st[2 * p + 1]);
	}
};
*/
// Dynamic answers to RangeMinimumQuery
class SegmentTree {
private:
	vi A, st; // A->data, st->tree (stores indices)
	int n; // length of the interval
	int left(int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }

	void build(int p, int L, int R) { // O(n)
		if (L == R)
			st[p] = L;
		else {
			build(left(p), L, (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R);
			int p1 = st[left(p)], p2 = st[right(p)];
			st[p] = (A[p1] <= A[p2]) ? p1 : p2;
		}
	}

	int rmq(int p, int L, int R, int i, int j) { // O(log n)
		// [L, R] -> interval of the node of the tree in which we are (p)
		// [i, j] -> interval of the query
		if (i > R || j < L) return -1; // totally outside
		if (L >= i && R <= j) return st[p]; // query is larger

		// if (st[p]>=i && st[p]<=j) return st[p]; better? 
		// Si es el minimo de un segmento mas largo, lo sera de uno contenido en ese

		int p1 = rmq(left(p), L, (L + R) / 2, i, j);
		int p2 = rmq(right(p), (L + R) / 2 + 1, R, i, j);

		if (p1 == -1) return p2;
		if (p2 == -1) return p1;
		return (A[p1] <= A[p2]) ? p1 : p2;
	}

	int updatePoint(int p, int L, int R, int idx, int new_value) { // O(log n)
		if (idx < L || idx > R) return st[p]; // no change
		if (L == idx && R == idx) { // leaf
			A[idx] = new_value; // we change it here to go up changing
			return st[p];
		}
		int p1 = updatePoint(left(p), L, (L + R) / 2, idx, new_value);
		int p2 = updatePoint(right(p), (L + R) / 2 + 1, R, idx, new_value);
		return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
	}

public:
	SegmentTree(const vi& a) {
		A = a; n = (int)a.size();
		st.assign(4 * n, 0);
		build(1, 0, n - 1);
	}

	int rmq(int i, int j) {
		return rmq(1, 0, n - 1, i, j);
	}

	void updatePoint(int idx, int new_value) {
		updatePoint(1, 0, n - 1, idx, new_value);
	}
};



void precalc(vi& euler, vi &prof, vi& first, int act, int profact, const vvii &tunnels, vector<long long int> &distToRoot,long long int distToRootAct) {
	euler.push_back(act);
	prof.push_back(profact);
	distToRoot[act] = min(distToRoot[act],distToRootAct);
	if (first[act] == -1)first[act] = euler.size() - 1;
	for (int i = 0; i < tunnels[act].size(); ++i) {
		precalc(euler, prof, first, tunnels[act][i].first, profact + 1, tunnels,distToRoot,distToRootAct+tunnels[act][i].second);
		euler.push_back(act);
		prof.push_back(profact);
	}
}

int main() {
	cin >> N;
	int src, dist, Q,S,T;
	while (N) {
		vvii tunnels(N);
		for (int i = 1; i <N; ++i) {			
			cin >> src>>dist;
			tunnels[src].push_back({ i, dist });
		}
		vi euler, prof, first(N, -1);
		vector<long long int> distToRoot(N,LLONG_MAX);
		precalc(euler, prof, first, 0, 0, tunnels, distToRoot,0);
		SegmentTree seg(prof);
		cin >> Q;
		cin >> S >> T;
		cout << distToRoot[S] + distToRoot[T] - 2 * distToRoot[euler[seg.rmq(min(first[S], first[T]), max(first[S], first[T]))]];
		for (int i = 1; i < Q; ++i) {
			cin >> S >> T;
			cout << ' '<< distToRoot[S] + distToRoot[T] - 2 * distToRoot[euler[seg.rmq(min(first[S], first[T]), max(first[S], first[T]))]];
		}
		cout << '\n';
		/*for (int i = 0; i < Q; ++i) {
			cin >> S >> T;
			cout << distToRoot[S] + distToRoot[T] - 2 * distToRoot[euler[segTreeRMQ.query(S, T)]] << " \n"[i==Q-1];
		}*/
		cin >> N;
	}
	return 0;
}