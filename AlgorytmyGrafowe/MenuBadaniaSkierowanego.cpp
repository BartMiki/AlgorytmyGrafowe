#include "MenuBadaniaSkierowanego.h"

int MenuBadaniaSkierowanego::wczytanieGnk(int rozmiar) {
	int k;
	system("cls");
	int maks = rozmiar*(rozmiar - 1);
	std::string tekst = ("k powinno przyjmowac wartosc od 0 do " + std::to_string(maks));
	wyswietlTekst({ "W generacji G(n,k), k oznacza maksymalna liczbe krawedzi.",
		tekst,
		"Podaj wartosc k:"
	});
	while (true) {
		std::cin >> k;
		if (std::cin.good())
			if (k <= maks && k >= 0)
				return k;
		std::cin.clear();
		std::cin.ignore();
		system("cls");
		wyswietlTekst({ "Ups, cos poszlo nie tak!",
			tekst,
			"Podaj wartosc k:"
		});
	}
}

char MenuBadaniaSkierowanego::wyswietlanieBadanie() {
	system("cls");
	wyswietlTekst({ "Dostepne opcje:",
		" a) Wyswietl graf.",
		" b) Algorytm Dijkstry.",
		" c) Algorytm Bellmana-Forda.",
		" d) Algorytm Floyda-Warshalla.",
		" e) Algorytm BFS.",
		" f) Algorytm DFS."
	});
	char wybor;
	std::string znaki;
	std::cin >> znaki;
	wybor = znaki[0];
	return wybor;
}

void MenuBadaniaSkierowanego::interpretujMacierz(Macierz wynik, int poczatek, int koniec){
	std::cout << "\n\nNajnizszy koszt dojscia od wierzcholka " << poczatek
		<< "\ndo wierzcholka " << koniec << " to:\n";
	if (wynik.getMacierz(poczatek, koniec) == INT_MAX)
		std::cout << "Nie istnieje taka sciezka.\n";
	else
		std::cout << wynik.getMacierz(poczatek, koniec) <<"\n";
	std::cin.clear();
	std::cin.ignore();
	getchar();
	system("cls");
}

void MenuBadaniaSkierowanego::menu() {
	int rozmiar, p, k, f;
	ParaTablic paraTablic;
	int poczatek, koniec;
	rozmiar = wczytanieRozmiaru();
	system("cls");
	Skierowany graf(rozmiar);
	char wybor = generacja();
	switch (wybor) {
	case 'a':
	case 'A':
		p = wczytanieGnp();
		graf.Gnp(p);
		graf.losujWagi();
		break;
	case 'b':
	case 'B':
		k = wczytanieGnk(rozmiar);
		graf.Gnk(k);
		graf.losujWagi();
		break;
	case 'c':
	case 'C':
		f = wczytanieGnf(rozmiar);
		graf.Gnf(f);
		graf.losujWagi();
		break;
	case 'd':
	case 'D':
		wczytanieWlasnego();
		graf.dodajGraf();
		break;
	default:
		domyslneWczytanie();
		graf.Gnp(50);
		graf.losujWagi();
		break;
	}
	bool test = true;
	while (test) {
		wybor = wyswietlanieBadanie();
		switch (wybor) {
		case 'a':
		case 'A': //wyswietl graf
			graf.wyswietlTalice();
			graf.Graf::wyswietlGraf();
			break;
		case 'b':
		case 'B': //Dijkstry
			poczatek = wczytajPoczatek(rozmiar);
			koniec = wczytajKoniec(rozmiar);
			paraTablic = graf.algorytmDijkstry(poczatek);
			graf.wyswietlTalice();
			graf.wysietlSciezke(koniec, paraTablic);
			break;
		case 'c':
		case 'C': //BellmanaForda
			poczatek = wczytajPoczatek(rozmiar);
			koniec = wczytajKoniec(rozmiar);
			graf.algorytmBellmanaForda(poczatek, paraTablic);
			graf.wyswietlTalice();
			graf.wysietlSciezke(koniec, paraTablic);
			break;
		case 'd':
		case 'D': //Floyda Warshalla
			poczatek = wczytajPoczatek(rozmiar);
			koniec = wczytajKoniec(rozmiar);
			graf.wyswietlTalice();
			interpretujMacierz(graf.algorytmFloydaWarshalla(), poczatek, koniec);
			graf.Graf::wyswietlGraf();
			break;
		case 'e':
		case 'E': //bsf
			poczatek = wczytajPoczatek(rozmiar);
			graf.wyswietlGraf(graf.BSF(poczatek));
			break;
		case 'f':
		case 'F': //dsf
			poczatek = wczytajPoczatek(rozmiar);
			graf.wyswietlGraf(graf.DSF(poczatek));
			break;
		default:
			system("cls");
			test = false;
			break;
		}
	}
}
