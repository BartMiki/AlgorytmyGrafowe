#ifndef Nieskierowany_h
#define Nieskierowany_h
#include "Graf.h"
class Nieskierowany : public Graf{
	virtual void rysujPolaczenia(sf::RenderWindow &okno, sf::Color kolor);
public:
	Nieskierowany(int n):Graf::Graf(n){}
	//tworzenie grafu
	virtual void dodajGraf();
	//generacja grafu
	virtual void Gnp(int p);
	virtual void Gnk(int k);
	virtual void Gnf(int f);
	//dodawanie wag
	virtual void losujWagi();
	//wyswietlanie
	virtual void wyswietlGraf(std::queue<int> kolejka);
	virtual void rysujSciezke(int cel, ParaTablic tablice, std::stack<int> sciezka);
};

#endif
