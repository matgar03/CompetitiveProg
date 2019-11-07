#include <iostream>
#include <stack>
#include <string> 
#include <sstream>

using namespace std;
stack<long long int> pila;
bool bien;

void resuelve(istream &linea, long long int &sum) {
	
	long long int num;
	while (linea >> num && bien) {
		if (num > 0 && !pila.empty() && pila.top() == -1 * num) {
			pila.pop();
			break;
		}
		else if (num < 0 && (pila.empty() || num > pila.top())) {
			sum -= num;
			if (sum >= 0) bien = false;
			else {
				pila.push(num);
				resuelve(linea, num);
			}
		}
		else bien = false;
	}
	


}

int main() {
	string line;
	while (getline(cin, line)) {
		bien = true;
		long long int max = -10000001;
		stringstream linea(line);
		resuelve(linea, max);
		if (!pila.empty()) bien = false;
		if (bien) cout << ":-) Matrioshka!\n";
		else cout << ":-( Try again.\n";
		stack<long long int> pila2;
		pila = pila2;
	}
	return 0;
}