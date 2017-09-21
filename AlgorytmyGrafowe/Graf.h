#ifndef Graf_h
#define Graf_h
#include "Macierz.h"
#include "Rysuj.h"
#include "ZbiorRozlaczny.h"
#include <iostream>
#include <list>
#include <random>
#include <iomanip>
#include <stack>
#include <queue>

struct ParaTablic{
	std::vector<int> tabKosztow, tabPoprzednikow;
};
struct Wierzcholek{
	int indeks;
	int koszt;
};
using TablicaList = std::vector<std::list<Wierzcholek>>;

class Graf{
protected:
	//dane startowe;
	int rozmiar;
	Macierz macierzPrzyleglosci;
	TablicaList tablicaListWierzcholkow;
	std::vector<Punkt> tablicaKoordynatow;
	//----------------------
	void utworzTabliceList();
	int random(int min, int max);
	//modul rysowania
	Rysuj rysuj;
	void utworzTabliceKoordynatow();
	void rysujWierzcholki(sf::RenderWindow &okno);
	virtual void rysujPolaczenia(sf::RenderWindow &okno,sf::Color kolor = sf::Color::White) = 0;
public:
	Graf(int n);
	//tworzenie grafu
	virtual void dodajGraf() = 0;
	//generacja grafu
	virtual void Gnp(int p) = 0;
	virtual void Gnk(int k) = 0;
	virtual void Gnf(int f) = 0;
	//dodawanie wag
	virtual void losujWagi() = 0;
	//przeszukiwanie
	std::queue<int> BSF(int start);
	std::queue<int> DSF(int start);
	bool czySpojny(std::queue<int> kolejka);
	//kolorowanie grafu
	std::vector<int> kolorowanieGrafu();
	//znajdowanie scierzek w grafie
	ParaTablic algorytmDijkstry(int elementStartowy);
	bool algorytmBellmanaForda(int elementStartowy, ParaTablic &wynik);
	bool usprawnionyAlgorytmBellmanaForda(int elementStartowy, ParaTablic &wynik);
	Macierz algorytmFloydaWarshalla();
	//drzewa rozpinajace
	std::list<Krawedz> algorytmKruskala();
	std::list<Krawedz> algorytmPrima(int poczatek);
	//wyswietlanie
	void wyswietlMacierz();
	void wyswietlTalice();
	void wysietlSciezke(int cel, ParaTablic tablice);
	virtual void wyswietlGraf();
	virtual void wyswietlGraf(std::vector<int> kolory);
	virtual void wyswietlGraf(std::list<Krawedz> krawedzie);
	virtual void wyswietlGraf(std::queue<int> kolejka) = 0;
	virtual void rysujSciezke(int cel, ParaTablic tablice, std::stack<int> sciezka) = 0;
};

#endif