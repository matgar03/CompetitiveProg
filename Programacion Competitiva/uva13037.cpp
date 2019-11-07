#include <iostream>
#include <unordered_map>


using namespace std;

int ncasos;

const bool SNN[3] = { true,false,false };
const bool NSN[3] = { false,true,false };
const bool NNS[3] = { false,false,true };

void copy_arr(bool  (&b1)[3], const bool (&b2)[3] ) {
	for (int i = 0; i < 3; ++i) {
		b1[i] = b2[i];
	}
}


struct gente {
	bool tiene[3];
	int cant;
};

void solucion(int k) {
	unordered_map <int, gente> map;
	int nl, nr, ns;
	cin >> nl >> nr >> ns;
	int choco;
	gente aux;
	

	for (int i = 0; i < nl; ++i) {
		cin >> choco;
		copy_arr(aux.tiene, SNN);
		aux.cant = 1;
		map.insert(pair<int, gente>(choco,aux));
	}

	for (int i = 0; i < nr; ++i) {
		cin >> choco;
		auto it = map.find(choco);
		if (it == map.end()) {
			copy_arr(aux.tiene, NSN);
			aux.cant = 1;
			map.insert(pair<int, gente>(choco, aux));
		}
		else if (!it->second.tiene[1]) {
			++it->second.cant;
			it->second.tiene[1] = true;
		}
	}

	for (int i = 0; i < ns; ++i) {
		cin >> choco;
		auto it = map.find(choco);
		if (it == map.end()) {
			copy_arr(aux.tiene, NNS);
			aux.cant = 1;
			map.insert(pair<int, gente>(choco, aux));
		}
		else if (!it->second.tiene[2]) {
			++it->second.cant;
			it->second.tiene[2] = true;
		}
	}
	int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0;
	for (auto const& ent : map) {
		if (ent.second.cant == 1) {
			if (ent.second.tiene[0])++n1;
			else if (ent.second.tiene[1])++n3;
			else ++n5;
		 }
		else if (ent.second.cant == 2) {
			if (!ent.second.tiene[0])++n2;
			else if (!ent.second.tiene[1])++n4;
			else ++n6;
		}
	}

	cout << "Case #" << k << ":\n";
	cout << n1 << ' ' << n2 <<'\n';
	cout << n3 << ' ' << n4 << '\n';
	cout << n5 << ' ' << n6 << '\n';
}


int main() {
	
	cin >> ncasos;

	for (int i = 0; i < ncasos; ++i) {
		solucion(i + 1);
	}



	return 0;
}