#ifndef Rysuj_h
#define Rysuj_h
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

struct Punkt {
	int indeks;
	float x, y;
	void ustaw(float x, float y) {
		this->x = x;
		this->y = y;
	}
	void ustaw(float x, float y, int indeks) {
		this->x = x;
		this->y = y;
		this->indeks = indeks;
	}
};

class Rysuj{
	const float promienWierzcholka = 20.0;
	sf::Font *czcionka;
	Punkt obliczWystapienie(Punkt poczatek, Punkt koniec);
public:
	std::vector<sf::Color> tablicaKolorow;
	Rysuj();
	~Rysuj();
	void Linie(Punkt poczatek, Punkt koniec,
		sf::RenderWindow &okno, sf::Color kolor = sf::Color::White);
	void Strzalke(Punkt poczatek, Punkt koniec,
		int waga, sf::RenderWindow &okno, sf::Color kolor = sf::Color::White);
	void odwroconaStrzalke(Punkt poczatek, Punkt koniec,
		sf::RenderWindow &okno, sf::Color kolor = sf::Color::White);
	void PolaczenieSkierowanego(Punkt poczatek, Punkt koniec,
		int waga, sf::RenderWindow &okno, sf::Color kolor = sf::Color::White);
	void PolaczenieNieskierowanego(Punkt poczatek, Punkt koniec,
		int waga, sf::RenderWindow &okno, sf::Color kolor = sf::Color::White);
	void Wierzcholek(Punkt lokacja,sf::RenderWindow &okno,
		sf::Color kolor = sf::Color::White, sf::Color wypelnienie = sf::Color::Black);
};

#endif
