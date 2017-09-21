#ifndef Menu_h
#define Menu_h
#include <cstdlib>
//#include "Nieskierowany.h"
#include "Skierowany.h"
#include "Nieskierowany.h"
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

class Menu{
protected:
	void wyswietlTekst(std::vector<std::string> napisy);
	int wczytanieRozmiaru();
	char generacja();
	int wczytanieGnp();
	int wczytanieGnf(int rozmiar);
	void wczytanieWlasnego();
	void domyslneWczytanie();
	int wczytajPoczatek(int rozmiar);
	int wczytajKoniec(int rozmiar);
	void pomiarCzasu();
public:
	void Glowne();
};

#endif