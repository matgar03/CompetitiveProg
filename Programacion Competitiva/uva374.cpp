#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	long long int B, P, M;
	int max;
	vector<long long int> aux;
	aux.push_back(1);
	while (aux.size() < 61) {
		aux.push_back(aux[aux.size() - 1] * 2);

	}
	while (cin >> B >> P >> M) {
		vector<long long int> v;
		B %= M;
		if (B == 0 && P==0)cout << "0\n";
		else {
			v.push_back(B);
			while (v.size() - 1 <= log2(P)) {
				v.push_back((v[v.size() - 1] * v[v.size() - 1]) % M);
			}
			B = 1;
			int i = min(int(v.size() - 1), 61);
			while (P) {
				if (i == 0) {
					--P;
					B = (B * v[0]) % M;
				}
				else {
					if (aux[i] <= P) {
						P -= aux[i];
						B = (B * v[i]) % M;
					}
					else --i;
				}

			}
			cout << B << '\n';
		}
	}
	return 0;
}