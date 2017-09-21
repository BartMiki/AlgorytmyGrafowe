#ifndef ZbiorRozlaczny_h
#define ZbiorRozlaczny_h
#include <vector>

struct Krawedz {
	int poczatek, koniec, waga;
	Krawedz() {}
	Krawedz(int p, int k, int w) {
		poczatek = p;
		koniec = k;
		waga = w;
	}
};
//zbiory rozlaczne to po prostu tablica
//indeksy odpowiadaja innej tablicy, ktora posiada wartosci
//elemeny tego samego zbioru maja przypisane klucze
//kluczem jest zwykle reprezentant zbioru, czyli pierwszy element w tym zbiorze
//dzieki tej klasie szybko mozna sprawdzac, czy nie utworzymy cyklu w naszym drzie
//cylki nie moze byc w drzewach dlatego to takie wazne
class ZbiorRozlaczny {
	struct Wezel {
		int klucz, ranga;
	};
	std::vector<Wezel> zbior;
public:
	ZbiorRozlaczny(int &rozmiar);
	void utworzZbior(int &element);
	int znajdzZbior(int &element);
	void uniaZbiorow(Krawedz &krawedz);
};

#endif
