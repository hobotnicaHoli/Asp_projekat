#include <iostream>
#include <string>
#include <queue>
#include "pitanja.h"

using namespace std;

struct Elem {
	Pitanja* p;
	Elem* sled;
	Elem(Pitanja* p1, Elem* s = nullptr) : p(p1), sled(s) {}
};
Elem* prvi = nullptr;
Elem* posl = nullptr;
void dodaj(Pitanja* p) {
	Elem* trenutni = new Elem(p);
	if (!prvi) {
		prvi = posl = trenutni;
	}
	else {
		posl->sled = trenutni;
		posl = trenutni;
	}
}
Pitanja* pretragapitanja(Pitanja* pit) {
	Elem* tek = prvi;
	Pitanja* pitanje = nullptr;
	while (tek) {
		if (tek->p == pit) {
			pitanje = tek->p;
		}
		tek = tek->sled;
	}
	return pitanje;
}
void ispisPitanja() {
	Elem* tek = prvi;
	while (tek->sled) {
		cout << tek->p->dohvatipitanje() << ", ";
		tek = tek->sled;
	}
	cout << tek->p->dohvatipitanje() << endl;
}
void sortiranje() {
	Elem* tek = prvi;
	while (tek) {
		tek->p->sort();
		tek = tek->sled;
	}
}
Odgovori* pretragamaxodgovora(Pitanja* p) {
	queue<Odgovori*> redodgovora;
	int kap = p->dohvatibr1();
	for (int i = 0; i < kap; i++) {
		Odgovori* o1 = p->dohvelementniza(i);
		redodgovora.push(o1);
	}
	int maxocena = 0;
	Odgovori* resenje = nullptr;
	while (kap != 0) {
		int kap2 = 0;
		for (int i = 0; i < kap; i++) {
			Odgovori* o2 = redodgovora.front();
			if (o2->dohvatiocenu() > maxocena) {
				resenje = o2;
				maxocena = o2->dohvatiocenu();
			}
			redodgovora.pop();
			kap2 += o2->dohvatibr2();
			for (int j = 0; j < o2->dohvatibr2(); j++) {
				redodgovora.push(o2->dohvelementniza(j));
			}
		}
		kap = kap2;
	}
	return resenje;
}
Odgovori* pretragaodgovora(Pitanja* p, Odgovori* o) {
	queue<Pitanja*> redpitanja;
	queue<Odgovori*> redodgovora;
	redpitanja.push(p);
	int kap = p->dohvatibr1();
	for (int i = 0; i < kap; i++) {
		Odgovori* o1 = p->dohvelementniza(i);
		redodgovora.push(o1);
	}
	Odgovori* resenje = nullptr;
	while (kap != 0) {
		int kap2 = 0;
		for (int i = 0; i < kap; i++) {
			Odgovori* o2 = redodgovora.front();
			if (o2 == o) {
				resenje = o2;
			}
			redodgovora.pop();
			kap2 += o2->dohvatibr2();
			for (int j = 0; j < o2->dohvatibr2(); j++) {
				redodgovora.push(o2->dohvelementniza(j));
			}
		}
		kap = kap2;
	}
	return resenje;
}

int main() {
	Pitanja p1("Pitanje1");
	Pitanja p2("Pitanje2");

	dodaj(&p1);
	dodaj(&p2);

	Odgovori o1(10, "Odg1");
	Odgovori o2(12, "Odg2");
	Odgovori o3(13, "Odg3");
	Odgovori o4(14, "Odg4");
	Odgovori o5(15, "Odg5");
	Odgovori o6(16, "Odg6");
	Odgovori o7(17, "Odg7");
	Odgovori o8(18, "Odg8");
	Odgovori o9(19, "Odg9");
	Odgovori o10(20, "Odg10");
	Odgovori o11(21, "Odg11");

	o9.uvecaj(10);
	o8.uvecaj(10);

	o1.dodaj(&o4);
	o3.dodaj(&o7);
	o3.dodaj(&o8);
	o2.dodaj(&o5);
	o2.dodaj(&o6);
	p1.dodaj(&o1);
	p1.dodaj(&o2);
	p1.dodaj(&o3);
	o5.dodaj(&o9);
	o5.dodaj(&o10);
	o5.dodaj(&o11);
	p2.dodaj(&o4);
	p2.dodaj(&o9);
	p2.dodaj(&o10);

	Pitanja* pk = pretragapitanja(&p1);
	if (pk != nullptr) {
		cout << "Pronadjeno pitanje: " << endl;
		cout << pk->dohvatipitanje() << endl;
	}

	cout << "Ispis svih pitanja: " << endl;
	ispisPitanja();

	Odgovori* op = pretragaodgovora(&p1, &o11);
	if (op != nullptr) {
		cout << "Pretrazeni odgovor je: " << op->dohvatiodgovor() << endl;
	}
	else {
		cout << "Pretrazeni odgovor se ne nalazi u zadatom pitanju! " << endl;
	}

	cout << "Ispis prvog i drugog stabla sa svim svojim potomcima: " << endl;
	p1.ispis();
	p2.ispis();

	sortiranje();
	cout << "Ispis prvog i drugog stabla sa svim svojim potomcima nakon sortiranja: " << endl;
	p1.ispis();
	p2.ispis();

	Odgovori* omax = pretragamaxodgovora(&p2);
	cout << "Max odgovor u pitanju br 2 je: " << omax->dohvatiodgovor() << ", " << omax->dohvatiocenu() << endl;
	
	p1.brisanjeodgovorapokusaj2(&o2);
	cout << "Ispis prvog stabla nakon brisanja Odg8: " << endl;
	p1.ispis();

	p1.brisanjestabla();
	cout << "Ispis prvog stabla nakon brisanja: " << endl;
	p1.ispis();

}