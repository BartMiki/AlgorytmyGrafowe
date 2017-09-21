#include "ZbiorRozlaczny.h"

ZbiorRozlaczny::ZbiorRozlaczny(int & rozmiar){
	zbior.resize(rozmiar);
}

void ZbiorRozlaczny::utworzZbior(int & element){
	zbior[element].klucz = element;
	zbior[element].ranga = 0;
}

int ZbiorRozlaczny::znajdzZbior(int & element){
	if (zbior[element].klucz != element)
		zbior[element].klucz = znajdzZbior(zbior[element].klucz);
	return zbior[element].klucz;
}

void ZbiorRozlaczny::uniaZbiorow(Krawedz & krawedz){
	int
		u = znajdzZbior(krawedz.poczatek),//korzen drzewa u
		v = znajdzZbior(krawedz.koniec);//korzen drzewa v
	if (u != v) {//korzenie musza byc rozne
		if (zbior[u].ranga > zbior[v].ranga) {
			zbior[v].klucz = u;
		}
		else {
			zbior[u].klucz = v;
			if (zbior[u].ranga == zbior[v].ranga)
				zbior[v].ranga++;
		}
	}
}
