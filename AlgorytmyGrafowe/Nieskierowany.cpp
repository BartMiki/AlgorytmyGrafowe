#include "stdafx.h"
#include "Nieskierowany.h"

void Nieskierowany::rysujPolaczenia(sf::RenderWindow & okno,sf::Color kolor = sf::Color::White) {
	for (int i = 0; i < rozmiar; i++) {
		Punkt poczatek = tablicaKoordynatow[i];
		for (auto sasiad : tablicaListWierzcholkow[i]) {
			Punkt koniec = tablicaKoordynatow[sasiad.indeks];
			rysuj.PolaczenieNieskierowanego(poczatek, koniec, sasiad.koszt, okno,kolor);
		}
	}
}

void Nieskierowany::dodajGraf() {
	int i, j, w;
	std::cin >> i >> j >> w;
	while (!(i < 0 || i >= rozmiar || j < 0 || j >= rozmiar || i == j || w < 0)) {
		macierzPrzyleglosci.setMacierz(w, i, j);
		macierzPrzyleglosci.setMacierz(w, j, i);
		std::cin >> i >> j >> w;
	}
	utworzTabliceList();
}

void Nieskierowany::Gnp(int p) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = i + 1; j < rozmiar; j++) {
			if (random(0, 100) <= p) {
				macierzPrzyleglosci.setMacierz(1, i, j);
				macierzPrzyleglosci.setMacierz(1, j, i);
			}
		}
	}
	for (int i = 0; i < rozmiar; i++) {
		macierzPrzyleglosci.setMacierz(0, i, i);
	}
}

void Nieskierowany::Gnk(int k) {
	std::vector<std::pair<int, int>> _tablicaPar;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = i + 1; j < rozmiar; j++) {
			std::pair<int, int> para(i, j);
			_tablicaPar.push_back(para);
		}
	}
	if (k > _tablicaPar.size())
		k = _tablicaPar.size();
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < _tablicaPar.size(); j++) {
			int indeks = random(j, _tablicaPar.size() - 1);
			std::swap(_tablicaPar[j], _tablicaPar[indeks]);
		}
	}
	for (int i = 0; i < k; i++) {
		macierzPrzyleglosci.setMacierz(1, _tablicaPar[i].first, _tablicaPar[i].second);
		macierzPrzyleglosci.setMacierz(1, _tablicaPar[i].second, _tablicaPar[i].first);
	}
	for (int i = 0; i < rozmiar; i++) {
		macierzPrzyleglosci.setMacierz(0, i, i);
	}
}

void Nieskierowany::Gnf(int f) {
	std::vector<std::pair<int, int>> _tablicaPar;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = i + 1; j < rozmiar; j++) {
			std::pair<int, int> para(i, j);
			_tablicaPar.push_back(para);

		}
	}
	std::vector<int> _tablicaStopi;
	for (int i = 0; i < rozmiar; i++) {
		_tablicaStopi.push_back(0);
	}
	//mechanizm bezpieczenstwa
	if (f > rozmiar)
		f = rozmiar;
	int wylosowane = 0; //oznacza indeks ostatnio wylosowanego elementu
	for (int i = 0; i < _tablicaPar.size(); i++) {
		int indeks = random(wylosowane, _tablicaPar.size() - 1);
		if (_tablicaStopi[_tablicaPar[indeks].first] < f && _tablicaStopi[_tablicaPar[indeks].second] <f) {
			_tablicaStopi[_tablicaPar[indeks].first]++;
			_tablicaStopi[_tablicaPar[indeks].second]++;
			std::swap(_tablicaPar[wylosowane], _tablicaPar[indeks]);
			wylosowane++;
		}
	}
	for (int i = 0; i < wylosowane; i++) {
		macierzPrzyleglosci.setMacierz(1, _tablicaPar[i].first, _tablicaPar[i].second);
		macierzPrzyleglosci.setMacierz(1, _tablicaPar[i].second, _tablicaPar[i].first);
	}
	for (int i = 0; i < rozmiar; i++) {
		macierzPrzyleglosci.setMacierz(0, i, i);
	}
}

void Nieskierowany::losujWagi() {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = i + 1; j < rozmiar; j++) {
			if (macierzPrzyleglosci.getMacierz(i, j) != 0) {
				int losowy = random(1, rozmiar);
				macierzPrzyleglosci.setMacierz(losowy, i, j);
				macierzPrzyleglosci.setMacierz(losowy, j, i);
			}
		}
	}
	utworzTabliceList();
}

void Nieskierowany::wyswietlGraf(std::queue<int> kolejka) {
	std::vector<Punkt> tablicaPunktow;
	while (!kolejka.empty()) {
		tablicaPunktow.push_back(tablicaKoordynatow[kolejka.front()]);
		kolejka.pop();
	}
	sf::RenderWindow okno(sf::VideoMode(1000, 1000, 32), "Graf");
	while (okno.isOpen()) {
		okno.clear(sf::Color(sf::Color::Black));
		rysujPolaczenia(okno,sf::Color(33,33,33));
		rysujWierzcholki(okno);
		for (int i = 1; i < tablicaPunktow.size(); i++) {
			rysuj.PolaczenieNieskierowanego(tablicaPunktow[i - 1], tablicaPunktow[i],
				macierzPrzyleglosci.getMacierz(tablicaPunktow[i - 1].indeks,
					tablicaPunktow[i].indeks), okno, sf::Color::Red);
			rysuj.Wierzcholek(tablicaPunktow[i - 1], okno, sf::Color::Red);
			rysuj.Wierzcholek(tablicaPunktow[i], okno, sf::Color::Red);
		}
		sf::Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				okno.close();
			}
		}
		okno.display();
	}
}

void Nieskierowany::rysujSciezke(int cel, ParaTablic tablice, std::stack<int> sciezka) {
	sf::RenderWindow okno(sf::VideoMode(1000, 1000, 32), "Graf");
	std::vector<Punkt> tablicaPunktow;
	while (okno.isOpen()) {
		okno.clear(sf::Color(sf::Color::Black));
		rysujPolaczenia(okno, sf::Color(33, 33, 33));
		rysujWierzcholki(okno);
		while (!sciezka.empty()) {
			tablicaPunktow.push_back(tablicaKoordynatow[sciezka.top()]);
			sciezka.pop();
		}
		for (int i = 1; i < tablicaPunktow.size(); i++) {
			rysuj.PolaczenieNieskierowanego(tablicaPunktow[i - 1], tablicaPunktow[i],
				tablice.tabKosztow[tablicaPunktow[i].indeks] -
				tablice.tabKosztow[tablicaPunktow[i - 1].indeks],
				okno, sf::Color::Red);
			rysuj.Wierzcholek(tablicaPunktow[i - 1], okno, sf::Color::Red);
			rysuj.Wierzcholek(tablicaPunktow[i], okno, sf::Color::Red);
		}
		sf::Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				okno.close();
			}
		}
		okno.display();
	}
}
