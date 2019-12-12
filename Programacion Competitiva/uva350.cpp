#include <iostream>

using namespace std;
int Z, I, M, L;

int f(int x0) {
	return (Z * x0 + I) % M;
}

typedef pair<unsigned int, unsigned int> uu;
uu floydCycleFinding(unsigned int x0) {
	int tortoise = f(x0), hare = f(f(x0));
	while (tortoise != hare) {
		tortoise = f(tortoise); hare = f(f(hare));
	}
	int mu = 0; hare = x0;
	while (tortoise != hare) {
		tortoise = f(tortoise); hare = f(hare); mu++;
	}
	int lambda = 1; hare = f(tortoise);
	while (tortoise != hare) {
		hare = f(hare); lambda++;
	}
	return uu(mu, lambda);
}


int main() {
	cin >> Z >> I >> M >> L;
	int cont = 1;
	while (Z != 0 || I != 0 || M != 0 || L != 0) {
		cout <<"Case "<<cont<<": "<< floydCycleFinding(L).second << '\n';
		cin >> Z >> I >> M >> L; ++cont;
	}
	return 0;
}