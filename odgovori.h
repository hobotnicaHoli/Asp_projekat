#ifndef _odgovori_h_
#define _odgovori_h_
#include <string>

using namespace std;

class Odgovori {

	int ocena = 0;
	Odgovori** o;
	string odgovor;
	int br = 0;
	string otac;

public:
	friend class Pitanja;
	Odgovori(int oc = 0, string s = "") : ocena(oc), odgovor(s) {
		o = new Odgovori*[10];
	}
	void dodaj(Odgovori* odg) {
		if (br < 10) {
			o[br++] = odg;
		}
	}
	string dohvatiodgovor() const {
		return odgovor;
	}
	int dohvatibr2() const {
		return br;
	}
	Odgovori* dohvelementniza(int i) {
		return o[i];
	}
	void uvecaj(int o) {
		ocena+=o;
	}
	int dohvatiocenu() const {
		return ocena;
	}
	~Odgovori() {
	}
};

#endif
