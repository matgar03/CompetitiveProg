#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 2;
int N;


class Trie {
	int prefixes;
	int words;
	std::vector<Trie*> child;
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
			if (child[*s - '0'] == nullptr) {
				t = child[*s - '0'] = new Trie();
				t->prefixes = 1;
			}
			else {
				t = child[*s - '0'];
				t->prefixes++;
			}
			t->add(s + 1);
		}
	}
};

int main() {
	cin >> N;
	int tam;
	while(N--) {
		cin >> tam;
		vector<vector<char>> v(tam, vector<char>(tam));
		for (int i = 0; i < tam; ++i) {
			for (int j = 0; j < tam; ++j)cin >> v[i][j];
		}
		Trie* ar = new Trie();
		for (int i = 0; i < tam; ++i) {
			for (int j = 0; j < tam; ++j) {
				ar->add(&v[i][0]);
			}
		}
	}
	return 0;
}