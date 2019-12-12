#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;
const int MAXN = 26;
int N,P;

class Trie {
	int prefixes;
	int words;
	vector<Trie*> child;
public:
	
	Trie() :prefixes(0), words(0), child(MAXN, nullptr) {}
	~Trie() {
		for (int i = 0; i < MAXN; ++i)
			delete child[i];
	}
	int pref() {
		return prefixes;
	}
	int word() {
		return words;
	}

	vector<Trie*> children() {
		return child;
	}


	void add(const char* s) {
		if (*s == '\0') ++words;
		else {
			Trie* t;
			if (child[*s - 'a'] == nullptr) {
				t = child[*s - 'a'] = new Trie();
				t->prefixes = 1;
			}
			else {
				t = child[*s - 'a'];
				t->prefixes++;
			}
			t->add(s + 1);
		}
	}
};

void pulsaciones(Trie* ar, int puls) {
	P =P+ ar->word() * puls;
	int hijos = 0;
	for (int i = 0; i < 26; ++i) {
		if (ar->children()[i] != nullptr) {
			++hijos;
			pulsaciones(ar->children()[i], puls + 1);
		}
	}
	if (hijos == 1 && ar->word()==0)P =P - ar->pref();

}

int main() {
	char* s= new char[100];
	cout << fixed << setprecision(2);
	while (cin >> N) {
		P = 0;
		Trie* ar = new Trie();
		for (int i = 0; i < N; ++i) {
			cin >> s;
			ar->add(s);
		}
		for (int i = 0; i < 26; ++i) {
			if (ar->children()[i] != nullptr) {
				pulsaciones(ar->children()[i], 1);
			}
		}
		long double sol;
		sol = 1.0 * round(100.0 * P / N) / 100;
		cout << sol << '\n';

	}
	return 0;
}