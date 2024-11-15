#ifndef _pitanja_h_
#define _pitanja_h_
#include <string>
#include <queue>
#include "odgovori.h"

using namespace std;

class Pitanja{

	Odgovori** odg;
	string pitanje;
	int br = 0;

public:
	Pitanja(string s = "") : pitanje(s){
		odg = new Odgovori*[10];
	}
	void ispis() const {
		cout << "Pitanje: " << pitanje << endl;
		queue<Odgovori*> redodgovora;
		int kap = br;
		for (int i = 0; i < kap; i++) {
			redodgovora.push(odg[i]);
			odg[i]->otac = pitanje;
		}
		while (kap != 0) {
			int kap2 = 0;
			for (int i = 0; i < kap; i++) {
				Odgovori* o2 = redodgovora.front();
				cout << o2->odgovor << ", " << o2->ocena << "(Odgovor na: '" << o2->otac  << "')"<< endl;
				redodgovora.pop();
				kap2 += o2->br;
				for (int j = 0; j < o2->br; j++) {
					redodgovora.push(o2->o[j]);
					o2->o[j]->otac = o2->odgovor;
				}
				
			}
			kap = kap2;
		}
	}
	int dohvatibr1() const {
		return br;
	}
	string dohvatipitanje() const {
		return pitanje;
	}
	Odgovori* dohvelementniza(int i) {
		return odg[i];
	}
	void dodaj(Odgovori* o) {
		if (br < 10) {
			odg[br] = o;
			br++;
		}
	}
	void sort() {
		queue<Odgovori*> redodgovora;
		int kap = br;
		for (int i = 0; i < (kap-1); i++) {
			for (int j = (i+1); j < kap; j++) {
				if (odg[i]->dohvatiocenu() < odg[j]->dohvatiocenu()) {
					Odgovori* o3 = odg[i];
					odg[i] = odg[j];
					odg[j] = o3;
				}
			}
		}
		for (int i = 0; i < kap; i++) {
			redodgovora.push(odg[i]);
		}
		while (kap != 0) {
			int kap2 = 0;
			for (int i = 0; i < kap; i++) {
				Odgovori o2 = *redodgovora.front();
				redodgovora.pop();
				kap2 += o2.dohvatibr2();
				for (int j = 0; j < (o2.dohvatibr2()-1); j++) {
					for (int k = (j + 1); k < o2.dohvatibr2(); k++) {
						if (o2.dohvelementniza(j)->dohvatiocenu() < o2.dohvelementniza(k)->dohvatiocenu()) {
							Odgovori* o5 = o2.dohvelementniza(j);
							o2.o[j] = o2.dohvelementniza(k);
							o2.o[k] = o5;
						}
					}
				}
				for (int j = 0; j < o2.br; j++) {
					redodgovora.push(o2.o[j]);
				}
			}
			kap = kap2;
		}
	}
	void brisanjestabla() {
		queue<Odgovori*> redodgovora;
		int kap = br;
		for (int i = 0; i < kap; i++) {
			redodgovora.push(odg[i]);
		}
		if (br != 0) {
			delete[] odg;
			br = 0;
		}
		int kapacitet = br;
		while (kap != 0) {
			int kap2 = 0;
			for (int i = 0; i < kap; i++) {
				Odgovori* o2 = redodgovora.front();
				redodgovora.pop();
				kap2 += o2->br;
				for (int j = 0; j < o2->br; j++) {
					redodgovora.push(o2->o[j]);
				}
				if (o2->br != 0) {
					delete[] o2->o;
					o2->br = 0;
				}
				o2->~Odgovori();
			}
			kap = kap2;
		}
		this->~Pitanja();
	}

	void brisanjepokazivacanaodgovor(Odgovori* od1) {
		queue<Odgovori*> redodgovora;
		int kap = br;
		for (int i = 0; i < kap; i++) {
			Odgovori* o1 = odg[i];
			redodgovora.push(o1);
			if (odg[i] == od1) {
				if (i == kap - 1) {
					br--;
				}
				else {
					for (int j = i; j < br - 1; j++) {
						odg[j] = odg[j + 1];
					}
					br--;
				}
				return;
			}
		}
		while (kap != 0) {
			int kap2 = 0;
			for (int i = 0; i < kap; i++) {
				Odgovori* o2 = redodgovora.front();
				redodgovora.pop();
				kap2 += o2->dohvatibr2();
				for (int j = 0; j < o2->dohvatibr2(); j++) {
					if (o2->o[j] == od1) {
						if (j == o2->br - 1) {
							o2->br--;
						}
						else {
							for (int k = j; k < o2->br - 1; k++) {
								o2->o[k] = o2->o[k + 1];
							}
							o2->br--;
						}
						return;
					}
					redodgovora.push(o2->dohvelementniza(j));
				}
			}
			kap = kap2;
		}
	}
	void brisanjeodgovorapokusaj2(Odgovori* od) {
		brisanjepokazivacanaodgovor(od);
		queue<Odgovori*> redodgovora;
		int kap = od->br;
		for (int i = 0; i < kap; i++) {
			redodgovora.push(od->o[i]);
		}
		if (br != 0) {
			delete[] od->o;
			od->br = 0;
		}
		while (kap != 0) {
			int kap2 = 0;
			for (int i = 0; i < kap; i++) {
				Odgovori* o2 = redodgovora.front();
				redodgovora.pop();
				kap2 += o2->br;
				for (int j = 0; j < o2->br; j++) {
					redodgovora.push(o2->o[j]);
				}
				if (o2->br != 0) {
					delete[] o2->o;
					o2->br = 0;
				}
				o2->~Odgovori();
			}
			kap = kap2;
		}
		od->~Odgovori();
	}
	~Pitanja() {}
};

#endif
