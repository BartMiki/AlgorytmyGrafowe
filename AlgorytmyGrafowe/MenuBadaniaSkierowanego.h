#ifndef MenuBadaniaSkierowanego_h
#define MenuBadaniaSkierowanego_h
#include "Skierowany.h"
#include "Menu.h"

class MenuBadaniaSkierowanego : public Menu {
protected:
	int wczytanieGnk(int rozmiar);
	char wyswietlanieBadanie();
	void interpretujMacierz(Macierz wynik, int poczatek, int koniec);
public:
	void menu();
};

#endif