#include "stdafx.h"
#include "Graf.h"

void Graf::utworzTabliceKoordynatow() {
	for (int i = 0; i < rozmiar; i++) {
		float promien = 450.0f;
		float t = 2 * std::_Pi / rozmiar;
		t *= i;
		Punkt nowy;
		nowy.indeks = i;
		nowy.x = 500.0f + promien*cos(t);
		nowy.y = 500.0f + promien*sin(t);
		tablicaKoordynatow.push_back(nowy);
	}
}

void Graf::rysujWierzcholki(sf::RenderWindow & okno) {
	for (auto it : tablicaKoordynatow) {
		rysuj.Wierzcholek(it, okno);
	}
}

Graf::Graf(int n) {
	rozmiar = n;
	macierzPrzyleglosci.utworzMacierz(n);
	tablicaListWierzcholkow.resize(n);
	utworzTabliceKoordynatow();
}

void Graf::utworzTabliceList() {
	for (int i = 0; i < rozmiar; i++) {
		std::list<Wierzcholek> pomocLista;
		for (int j = 0; j < rozmiar; j++) {
			if (macierzPrzyleglosci.getMacierz(i, j) != 0) {
				Wierzcholek pomocWierzcholek;
				pomocWierzcholek.indeks = j;
				pomocWierzcholek.koszt = macierzPrzyleglosci.getMacierz(i, j);
				pomocLista.push_back(pomocWierzcholek);
			}
		}
		tablicaListWierzcholkow[i] = pomocLista;
	}
}

int Graf::random(int min, int max) {
	static std::random_device r;
	static std::default_random_engine e(r());
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}

bool Graf::czySpojny(std::queue<int> kolejka) {
	std::vector<bool> odwiedzone(rozmiar);
	for (auto &i : odwiedzone)
		i = false;
	while (!kolejka.empty()) {
		odwiedzone[kolejka.front()] = true;
		kolejka.pop();
	}
	for (auto i : odwiedzone)
		if (i == false)
			return false;
	return true;
}

std::queue<int> Graf::BSF(int start) {
	std::queue<int> sciezka, doOdwiedzenia;
	std::vector<bool> odwiedzone;
	odwiedzone.resize(rozmiar);
	for (auto &it : odwiedzone)
		it = false;
	sciezka.push(start);
	odwiedzone[start] = true;
	for (auto it = tablicaListWierzcholkow[start].begin();
		it != tablicaListWierzcholkow[start].end(); it++) {
		doOdwiedzenia.push(it->indeks);
	}
	while (!doOdwiedzenia.empty()) {
		start = doOdwiedzenia.front();
		odwiedzone[start] = true;
		doOdwiedzenia.pop();
		sciezka.push(start);
		for (auto it = tablicaListWierzcholkow[start].begin();
			it != tablicaListWierzcholkow[start].end(); it++) {
			if (!odwiedzone[it->indeks])
				doOdwiedzenia.push(it->indeks);
		}
	}
	return sciezka;
}

std::queue<int> Graf::DSF(int start) {
	std::queue<int> sciezka;
	std::stack<int> doOdwiedzenia;
	std::vector<bool> odwiedzone;
	odwiedzone.resize(rozmiar);
	for (auto &it : odwiedzone)
		it = false;
	odwiedzone[start] = true;
	sciezka.push(start);
	for (auto it = tablicaListWierzcholkow[start].rbegin();
		it != tablicaListWierzcholkow[start].rend(); it++) {
		doOdwiedzenia.push(it->indeks);
	}
	while (!doOdwiedzenia.empty()) {
		start = doOdwiedzenia.top();
		odwiedzone[start] = true;
		doOdwiedzenia.pop();
		sciezka.push(start);
		for (auto it = tablicaListWierzcholkow[start].rbegin();
			it != tablicaListWierzcholkow[start].rend(); it++) {
			if (!odwiedzone[it->indeks])
				doOdwiedzenia.push(it->indeks);
		}
	}
	return sciezka;
}

std::vector<int> Graf::kolorowanieGrafu() {
	//inicjalizacja
	using TabStopni = std::vector<std::pair<int, int>>; //pierwszy -> indeks, drugi -> stopien
	std::vector<int> tabKolorow;
	for (int i = 0; i < rozmiar; i++)
		tabKolorow.push_back(-1);
	std::vector<bool> koloryZajete;
	for (int i = 0; i < rozmiar; i++)
		koloryZajete.push_back(false);
	TabStopni tabStopni;
	for (int i = 0; i < rozmiar; i++) {
		tabStopni.push_back(std::pair<int, int>(i, tablicaListWierzcholkow[i].size()));
	}
	//sorowanie stopni
	std::sort(tabStopni.begin(), tabStopni.end(),
		[](const std::pair<int, int> &x, const std::pair<int, int> &y) -> bool
	{return (x.second > y.second); });
	//posortowane wierzcholki
	std::cout << "Posortowane wierzcholki wedlug stopni:\n"; {
		auto t = tabStopni.begin();
		std::cout << t->first << "[" << t->second << "]";
		for (++t; t != tabStopni.end(); t++) {
			std::cout << ", " << t->first << "[" << t->second << "]";
		}
		std::cout << "\n";
	}
	tabKolorow[tabStopni[0].first] = 0; //pierwszy wierzcholek ma pierwszy kolor
	for (int wierzcholek = 1; wierzcholek < rozmiar; wierzcholek++) {
		for (auto &i : koloryZajete)
			i = false;
		for (auto sasiad : tablicaListWierzcholkow[tabStopni[wierzcholek].first]) {
			if (tabKolorow[sasiad.indeks] > -1)
				koloryZajete[tabKolorow[sasiad.indeks]] = true;
		}
		int kolor;
		for (kolor = 0; koloryZajete[kolor]; kolor++);
		tabKolorow[tabStopni[wierzcholek].first] = kolor;
	}
	return tabKolorow;
}

ParaTablic Graf::algorytmDijkstry(int elementStartowy) {
	//inicjalizacja
	ParaTablic wynik;
	for (int i = 0; i < rozmiar; i++) {
		wynik.tabKosztow.push_back(INT_MAX);	//ustawiamy na nieskonczonosc
		wynik.tabPoprzednikow.push_back(-1);	//ustawiamy na -1 (nieistniejacy wierzcholek)
	}
	wynik.tabKosztow[elementStartowy] = 0; //nie ma kosztu dojscia do samego siebie 
										 //-------
										 //algorytm
	auto porownajWierzchoki = [](const Wierzcholek &x, const Wierzcholek &y)->bool {return(y.koszt < x.koszt); };
	std::priority_queue<Wierzcholek, std::vector<Wierzcholek>, decltype(porownajWierzchoki)>
		kolejka(porownajWierzchoki);
	Wierzcholek wierzcholek; wierzcholek.indeks = elementStartowy; wierzcholek.koszt = 0;
	kolejka.push(wierzcholek);
	while(!kolejka.empty()){
		int u = kolejka.top().indeks;//u to indeks badanego wierzcholka
		kolejka.pop();
		//teraz przeszukujemy liste sasiedztwa wierzcholka u
		for (auto w : tablicaListWierzcholkow[u]) {
			int koszt = wynik.tabKosztow[u] + w.koszt;
			if (wynik.tabKosztow[w.indeks] > koszt) { //relaksacja
				wynik.tabKosztow[w.indeks] = koszt;
				wynik.tabPoprzednikow[w.indeks] = u;
				wierzcholek.indeks = w.indeks;
				wierzcholek.koszt = w.koszt;
				kolejka.push(wierzcholek);
			}
		}
	}
	return wynik;
}

bool Graf::algorytmBellmanaForda(int elementStartowy, ParaTablic &wynik) {
	//inicjalizacja
	std::vector<int>
		tablicaKosztów,	//tablica kosztu dojscia do kazdego wiedzcholka od startu
		tablicaPoprzednikow; //tablica zawierajaca poprzednika o niejmniejszym koszcie
	for (int i = 0; i < rozmiar; i++) {
		tablicaKosztów.push_back(INT_MAX);	//ustawiamy na nieskonczonosc
		tablicaPoprzednikow.push_back(-1);	//ustawiamy na -1 (nieistniejacy wierzcholek)
	}
	tablicaKosztów[elementStartowy] = 0; //nie ma kosztu dojscia do samego siebie 
	for (int i = 1; i < rozmiar; i++) { //petla relaksacji
		for (int j = 0; j < rozmiar; j++) {  //przechodzimy wszystkie wierzcholki
			for (auto sasiad : tablicaListWierzcholkow[j]) { //iterujemy po sasiadach
				//warunek relakscaji
				if ((tablicaKosztów[sasiad.indeks] > (tablicaKosztów[j] + sasiad.koszt))
					&& tablicaKosztów[j] != INT_MAX) {
					//relaksacja krawedzi
					tablicaKosztów[sasiad.indeks] = tablicaKosztów[j] + sasiad.koszt;
					tablicaPoprzednikow[sasiad.indeks] = j; //nowy poprzednik sasiada
				}
			}
		}
	}
	//sprawdzanie czy istnieje cykl ujemny
	for (int i = 0; i < rozmiar; i++) {
		for (auto sasiad : tablicaListWierzcholkow[i]) {
			//sprawdzamy czy nadal istnieja krotsze sciezki
			if (tablicaKosztów[sasiad.indeks] > tablicaKosztów[i] + sasiad.koszt)
				return false; //znaleziono ujemny cylk
		}
	}
	wynik.tabKosztow = tablicaKosztów;
	wynik.tabPoprzednikow = tablicaPoprzednikow;
	return true;
}

bool Graf::usprawnionyAlgorytmBellmanaForda(int elementStartowy, ParaTablic &wynik) {
	//inicjalizacja
	std::vector<int>
		tablicaKosztów,	//tablica kosztu dojscia do kazdego wiedzcholka od startu
		tablicaPoprzednikow; //tablica zawierajaca poprzednika o niejmniejszym koszcie
	for (int i = 0; i < rozmiar; i++) {
		tablicaKosztów.push_back(INT_MAX);	//ustawiamy na nieskonczonosc
		tablicaPoprzednikow.push_back(-1);	//ustawiamy na -1 (nieistniejacy wierzcholek)
	}
	tablicaKosztów[elementStartowy] = 0; //nie ma kosztu dojscia do samego siebie 
	bool brakZmian;
	for (int i = 1; i < rozmiar; i++) { //petla relaksacji
		brakZmian = true;  //czy algorytm nie wprowadzil zmian
		for (int j = 0; j < rozmiar; j++) {  //przechodzimy wszystkie wierzcholki
			for (auto sasiad : tablicaListWierzcholkow[j]) { //iterujemy po sasiadach
															 //warunek relakscaji
				if ((tablicaKosztów[sasiad.indeks] >(tablicaKosztów[j] + sasiad.koszt))
					&& tablicaKosztów[j] != INT_MAX) {
					brakZmian = false; //nastepuje zmiana, czyli odbywa sie relaksacja
									   //relaksacja krawedzi
					tablicaKosztów[sasiad.indeks] = tablicaKosztów[j] + sasiad.koszt;
					tablicaPoprzednikow[sasiad.indeks] = j; //nowy poprzednik sasiada
				}
			}
		}
		//usprawnienie algorytmu polega na tym ze kiedy nie dokonano relaksacji w tym obiegu
		//oznacza to ze nie trzeba dalej sprawdzac bo nie bedzie juz poprawy
		if (brakZmian) {
			wynik.tabKosztow = tablicaKosztów;
			wynik.tabPoprzednikow = tablicaPoprzednikow;
			return true;
		}
	}
	//sprawdzanie czy istnieje cykl ujemny
	for (int i = 0; i < rozmiar; i++) {
		for (auto sasiad : tablicaListWierzcholkow[i]) {
			//sprawdzamy czy nadal istnieja krotsze sciezki
			if (tablicaKosztów[sasiad.indeks] > tablicaKosztów[i] + sasiad.koszt)
				return false; //znaleziono ujemny cylk
		}
	}
	wynik.tabKosztow = tablicaKosztów;
	wynik.tabPoprzednikow = tablicaPoprzednikow;
	return true;
}

Macierz Graf::algorytmFloydaWarshalla() {
	Macierz wynik;
	wynik.utworzMacierz(rozmiar);
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			int waga = macierzPrzyleglosci.getMacierz(i, j);
			if (waga == 0)
				wynik.setMacierz(INT_MAX, i, j);//jezeli nie ma polaczenia to koszt jest nieskoczony
			else
				wynik.setMacierz(waga, i, j);//jezeli polaczenie jest to koszt ustawiamy na wage
		}
		wynik.setMacierz(0, i, i);
	}
	for (int k = 0; k < rozmiar; k++) {
		for (int i = 0; i < rozmiar; i++) {
			for (int j = 0; j < rozmiar; j++) {
				if ((wynik.getMacierz(i, k) == INT_MAX) || (wynik.getMacierz(k, j) == INT_MAX))
					continue;
				int waga = wynik.getMacierz(i, k) + wynik.getMacierz(k, j);
				if (wynik.getMacierz(i, j) > waga) //jezeli mamy nizszy koszt dojscia to
					wynik.setMacierz(waga, i, j);
			}
		}
	}
	return wynik;
}

std::list<Krawedz> Graf::algorytmKruskala() {
	auto porownajKrawedzie = [](const Krawedz &x, const Krawedz &y)->bool {return(y.waga < x.waga); };
	std::priority_queue<Krawedz, std::vector<Krawedz>, decltype(porownajKrawedzie)>
		listaKrawedzi(porownajKrawedzie);
	std::list<Krawedz> wynik;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = i + 1; j < rozmiar; j++) {
			if (macierzPrzyleglosci[i][j] == 0)
				continue;
			Krawedz nowa(i, j, macierzPrzyleglosci[i][j]);
			listaKrawedzi.push(nowa);
		}
	}
	//tworzymy zbiory rozlaczne
	ZbiorRozlaczny zbior(rozmiar);
	for (int i = 0; i < rozmiar; i++) {
		zbior.utworzZbior(i);
	}
	//przetwarzamy wierzcholki
	Krawedz krawedz;
	for (int i = 1; i < rozmiar; i++) {
		do {
			krawedz = listaKrawedzi.top();
			listaKrawedzi.pop();
		} while (zbior.znajdzZbior(krawedz.poczatek) == zbior.znajdzZbior(krawedz.koniec));
		wynik.push_back(krawedz);
		zbior.uniaZbiorow(krawedz);
	}
	return wynik;
}

std::list<Krawedz> Graf::algorytmPrima(int poczatek) {
	auto porownajKrawedzie = [](const Krawedz &x, const Krawedz &y)->bool {return(y.waga < x.waga); };
	std::priority_queue<Krawedz, std::vector<Krawedz>, decltype(porownajKrawedzie)>
		listaKrawedzi(porownajKrawedzie);
	std::list<Krawedz> wynik;
	std::vector<bool> odwiedzone(rozmiar);
	for (auto& i : odwiedzone) {
		i = false;
	}
	odwiedzone[poczatek] = true;
	//przetwarzamy wierzcholki
	Krawedz krawedz;
	for (int i = 1; i < rozmiar; i++) {
		for (auto sasiad : tablicaListWierzcholkow[poczatek]) {
			if (!odwiedzone[sasiad.indeks]) {
				krawedz.poczatek = poczatek;
				krawedz.koniec = sasiad.indeks;
				krawedz.waga = sasiad.koszt;
				listaKrawedzi.push(krawedz);
			}
		}
		do {
			krawedz = listaKrawedzi.top();
			listaKrawedzi.pop();
		} while (odwiedzone[krawedz.koniec]); //szukamy krawedzi ktora prowadzi poza drzewo
		wynik.push_back(krawedz);
		odwiedzone[krawedz.koniec] = true;
		poczatek = krawedz.koniec;	//nowym poczatkiem jest znalezona krawedz z poza drzewa
									//ktora jest juz w drzewie
	}
	return wynik;
}

void Graf::wysietlSciezke(int cel, ParaTablic tablice) {
	std::stack<int> sciezka;
	//przechodzimy sciezke od konca do poczatku
	for (int i = cel; i > -1; i = tablice.tabPoprzednikow[i]) {
		sciezka.push(i);
	}
	int poczatek;
	for (int i = 0; i < tablice.tabPoprzednikow.size(); i++) {
		if (tablice.tabPoprzednikow[i] == -1) {
			poczatek = i;
			break;
		}
	}
	std::stack<int> wynik = sciezka;
	std::cout << "Sciezka od wierzcholka " << sciezka.top() << " do wierzcholka "
		<< cel << " to jest:\n";
	if (!sciezka.empty()) {
		if (tablice.tabKosztow[sciezka.top()] == INT_MAX) {
			std::cout << "Nie ma sciezki miedzy wierzcholkami\n";
			std::cin.ignore();
			getchar();
		}
		else {
			std::cout << "[" << sciezka.top() << "," << tablice.tabKosztow[sciezka.top()] << "] ";
			sciezka.pop();
			while (!sciezka.empty()) {
				std::cout << "-> [" <<
					sciezka.top() << "," << tablice.tabKosztow[sciezka.top()] << "] ";
				sciezka.pop();
			}
			rysujSciezke(cel, tablice, wynik);
		}
	}
}

void Graf::wyswietlGraf() {
	sf::RenderWindow okno(sf::VideoMode(1000, 1000, 32), "Graf");
	while (okno.isOpen()) {
		okno.clear(sf::Color(sf::Color::Black));
		rysujPolaczenia(okno);
		rysujWierzcholki(okno);
		sf::Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				okno.close();
			}
		}
		okno.display();
	}
}

void Graf::wyswietlGraf(std::vector<int> kolory) {
	sf::RenderWindow okno(sf::VideoMode(1000, 1000, 32), "Graf");
	for (int i = 0; i < rozmiar; i++) {
		std::cout << "\n" << i << " z kolorem: " << kolory[i];
	}
	while (okno.isOpen()) {
		okno.clear(sf::Color(sf::Color::Black));
		rysujPolaczenia(okno, sf::Color(33, 33, 33));
		int i = 0;
		for (auto it : tablicaKoordynatow) {
			rysuj.Wierzcholek(it, okno, sf::Color::Black,
				rysuj.tablicaKolorow[kolory[i]]);
			i++;
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

void Graf::wyswietlGraf(std::list<Krawedz> krawedzie) {
	sf::RenderWindow okno(sf::VideoMode(1000, 1000, 32), "Graf");
	system("cls");
	int koszt = 0;
	for (auto i : krawedzie) {
		std::cout << i.poczatek << " - " << i.koniec << ": " << i.waga << "\n";
		koszt += i.waga;
	}
	std::cout << "Calkowity koszt drzewa to: " << koszt << ".\n";
	while (okno.isOpen()) {
		okno.clear(sf::Color(sf::Color::Black));
		rysujPolaczenia(okno, sf::Color(33, 33, 33));
		rysujWierzcholki(okno);
		for (auto it : krawedzie) {
			rysuj.PolaczenieNieskierowanego(tablicaKoordynatow[it.poczatek], tablicaKoordynatow[it.koniec],
				it.waga, okno, sf::Color::Red);
			rysuj.Wierzcholek(tablicaKoordynatow[it.poczatek], okno, sf::Color::Red);
			rysuj.Wierzcholek(tablicaKoordynatow[it.koniec], okno, sf::Color::Red);
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

void Graf::wyswietlMacierz() {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			std::cout << std::setw(3);
			std::cout << macierzPrzyleglosci.getMacierz(i, j);
		}
		std::cout << "\n";
	}
}

void Graf::wyswietlTalice() {
	int numer = 0;
	system("cls");
	std::cout << "Tablica list sasiadow z wagami:\n";
	for (auto i : tablicaListWierzcholkow) {
		std::cout << numer++ << "->";
		for (auto j : i) {
			std::cout << " [" << j.indeks << "," << j.koszt << "] ";
		}
		std::cout << "\n";
	}
}