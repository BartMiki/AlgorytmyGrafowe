#ifndef MenuBadaniaNieSkierowanego_h
#define MenuBadaniaNieSkierowanego_h
#include "Menu.h"
class MenuBadaniaNieSkierowanego : public Menu{
protected:
	int wczytanieGnk(int rozmiar);
	char wyswietlanieBadanie();
	void interpretujMacierz(Macierz wynik, int poczatek, int koniec);
public:
	void menu();
};

#endif

