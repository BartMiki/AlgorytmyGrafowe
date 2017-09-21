#include "Menu.h"
#include "MenuBadaniaSkierowanego.h"
#include "MenuBadaniaNieSkierowanego.h"
 
void Menu::wyswietlTekst(std::vector<std::string> napisy){
	int max = 0;
	for (auto i : napisy) {
		if (i.size() > max)
			max = i.size();
	}
	max += 2;
	char lewyGorny = 201, prawyGorny = 187, lewyDolny = 200,
		prawyDolny = 188, bok = 186, belka = 205;
	std::cout << lewyGorny;
	for (int i = 0; i < max; i++)std::cout << belka;
	std::cout << prawyGorny << '\n';
	for (auto i : napisy) {
		std::cout << bok << " ";
		std::cout << std::setw(max-2) <<std::left;
		std::cout << i << " " << bok << '\n';
	}
	std::cout << lewyDolny;
	for (int i = 0; i < max; i++)std::cout << belka;
	std::cout << prawyDolny << '\n';
}

int Menu::wczytanieRozmiaru() {
	system("cls");
	wyswietlTekst({ "Witaj w sekscji badania grafow!",
		"Na poczatku okresl stopien grafu.",
		"Watosc powinna byc z zakresu 1-15:" });
	int rozmiar;
	while (true) {
		std::cin >> rozmiar;
		if (std::cin.good())
			if (!(rozmiar > 15 || rozmiar < 1))
				return rozmiar;
		std::cin.clear();
		std::cin.ignore();
		system("cls");
		wyswietlTekst({ "Ups, cos poszlo nie tak!",
			"Prosze wpisz poprawna wartosc",
			"z zakresu 1-15:"
		});
	}
}

char Menu::generacja() {
	wyswietlTekst({
		"Teraz trzeba wygenerowac graf",
		"Wybierz jedna z automatycznych generacji,",
		"albo wpisz wlasny graf.",
		" a) G(n,p)",
		" b) G(n,k)",
		" c) G(n,f)",
		" d) Reczne wpisanie"
	});
	char wybor;
	std::string znaki;
	std::cin >> znaki;
	wybor = znaki[0];
	return wybor;
}

int Menu::wczytanieGnp() {
	int p;
	system("cls");
	wyswietlTekst({ "W generacji G(n,p), p oznacza",
		"prawdopodobienstwo krawedziowe.",
		"Prosze podaj wartosc w procentach:"
	});
	while (true) {
		std::cin >> p;
		if (std::cin.good())
			if (p <= 100 && p >= 0)
				return p;
		std::cin.clear();
		std::cin.ignore();
		system("cls");
		wyswietlTekst({ "Ups, cos poszlo nie tak!",
			"Prosze podac wartosc z zakresu 0-100.",
			"Podaj wartosc p:"
		});
	}
}

int Menu::wczytanieGnf(int rozmiar) {
	int f;
	system("cls");
	int maks = rozmiar - 1;
	std::string tekst = ("f powinno przyjmowac wartosc od 0 do " + std::to_string(maks));
	wyswietlTekst({ "W generacji G(n,f), f oznacza maksymalny stopien wierzcholka.",
		tekst,
		"Podaj wartosc f:"
	});
	while (true) {
		std::cin >> f;
		if (std::cin.good())
			if (f <= maks && f >= 0)
				return f;
		std::cin.clear();
		std::cin.ignore();
		system("cls");
		wyswietlTekst({ "Ups, cos poszlo nie tak!",
			tekst,
			"Podaj wartosc f:"
		});
	}
}

void Menu::wczytanieWlasnego() {
	system("cls");
	wyswietlTekst({ "Schemat wpisywania grafu to:",
		"Wierzcholek_Poczatkowy, Wierzcholek_Koncowy, Waga_Krawedzi.",
		"Np: 2 4 9",
		"Tworzy krawedz z waga 9 od wierzcholka 2 do 4.",
		"Mozna nadpisywac utworzone wierzcholki.",
		"Podanie niewlasciwych danych konczy wpisywanie."
	});
}

void Menu::domyslneWczytanie() {
	system("cls");
	wyswietlTekst({ "Nie wybrano poprawnej opcji.",
		"Przypisano domyslny graf G(n,p),",
		"gdzie p = 50%"
	});
}

int Menu::wczytajPoczatek(int rozmiar) {
	int poczatek;
	system("cls");
	wyswietlTekst({ "Podaj poczatek sciezki:" });
	while (true) {
		std::cin >> poczatek;
		if (std::cin.good())
			if (!(poczatek<0 || poczatek >= rozmiar))
				return poczatek;
		std::cin.clear();
		std::cin.ignore();
		std::string zakres;
		zakres = std::to_string(rozmiar - 1);
		system("cls");
		wyswietlTekst({ "Ups, cos poszlo nie tak!",
			"Prosze wpisz poprawna wartosc",
			"z zakresu 0-" + zakres + ":"
		});
	}
}

int Menu::wczytajKoniec(int rozmiar) {
	int koniec;
	system("cls");
	wyswietlTekst({ "Podaj koniec sciezki:" });
	while (true) {
		std::cin >> koniec;
		if (std::cin.good())
			if (!(koniec<0 || koniec >= rozmiar))
				return koniec;
		std::cin.clear();
		std::cin.ignore();
		std::string zakres;
		zakres = std::to_string(rozmiar - 1);
		system("cls");
		wyswietlTekst({ "Ups, cos poszlo nie tak!",
			"Prosze wpisz poprawna wartosc",
			"z zakresu 0-" + zakres + ":"
		});
	}
}

void Menu::pomiarCzasu(){
	const int limit = 301;
	int licznik=0;
	int rozmiar=0;
	int
		kruskala = 0.0,
		prima = 0.0,
		dijkstry = 0.0,
		bellmana_forda = 0.0,
		us_bellmana_forda = 0.0,
		floyda_warshalla = 0.0,
		bsf = 0.0,
		dsf = 0.0;
	system("cls");
	wyswietlTekst({ "Witaj w sekcji badania czasu algortmow.",
		"Rozpatrywane grafy beda grafami nieskierowanymi.",
		"Na poczatku podaj wielkosc grafu:" });
	while (true) {
		std::cin >> rozmiar;
		if (std::cin.good())
			if (rozmiar>0)
				break;
		std::cin.clear();
		std::cin.ignore();
		system("cls");
		wyswietlTekst({ "Ups, cos poszlo nie tak!","Wpisz wartosc dodatnia."});
	}
	system("cls");
	wyswietlTekst({ "Podaj ilosc pomiarow:"});
	while (true) {
		std::cin >> licznik;
		if (std::cin.good())
			if (rozmiar>0)
				break;
		std::cin.clear();
		std::cin.ignore();
		system("cls");
		wyswietlTekst({ "Ups, cos poszlo nie tak!","Wpisz wartosc dodatnia." });
	}
	for (int i = 0; i < licznik;) {
		Nieskierowany graf(rozmiar);
		graf.Gnp(50);
		graf.losujWagi();
		if (graf.czySpojny(graf.BSF(0))) {
			system("cls");
			std::cout << "Iteracja " << i + 1 << " z " << licznik <<"\n";
			//-------------------
			std::cout << " . ";
			auto start = std::chrono::system_clock::now();
			graf.algorytmKruskala();
			auto stop = std::chrono::system_clock::now();
			auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			kruskala += czas.count();
			//-------------------
			std::cout << " . ";
			start = std::chrono::system_clock::now();
			graf.algorytmPrima(0);
			stop = std::chrono::system_clock::now();
			czas = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			prima += czas.count();
			//-------------------
			std::cout << " . ";
			start = std::chrono::system_clock::now();
			graf.algorytmDijkstry(0);
			stop = std::chrono::system_clock::now();
			czas = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			dijkstry += czas.count();
			//-------------------
			std::cout << " . ";
			start = std::chrono::system_clock::now();
			ParaTablic wynik;
			graf.algorytmBellmanaForda(0, wynik);
			stop = std::chrono::system_clock::now();
			czas = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			bellmana_forda += czas.count();
			//-------------------
			std::cout << " . ";
			start = std::chrono::system_clock::now();
			wynik;
			graf.usprawnionyAlgorytmBellmanaForda(0, wynik);
			stop = std::chrono::system_clock::now();
			czas = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			us_bellmana_forda += czas.count();
			//-------------------
			if (rozmiar < limit) {
				std::cout << " . ";
				start = std::chrono::system_clock::now();
				graf.algorytmFloydaWarshalla();
				stop = std::chrono::system_clock::now();
				czas = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
				floyda_warshalla += czas.count();
			}
			//-------------------
			std::cout << " . ";
			start = std::chrono::system_clock::now();
			graf.BSF(0);
			stop = std::chrono::system_clock::now();
			czas = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			bsf+= czas.count();
			//-------------------
			std::cout << " . ";
			start = std::chrono::system_clock::now();
			graf.DSF(0);
			stop = std::chrono::system_clock::now();
			czas = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			dsf += czas.count();
			//-------------------
			i++;
		}
	}
	kruskala /= licznik;
	prima /= licznik;
	dijkstry /= licznik;
	bellmana_forda /= licznik;
	us_bellmana_forda /= licznik;
	floyda_warshalla /= licznik;
	bsf /= licznik;
	dsf /= licznik;
	system("cls");
	wyswietlTekst({ "Wyniki pomiaru:" });
	std::cout << "\nAlgorytm Dijkstry: " << dijkstry / 1000 << " sekund, " << dijkstry%1000 << " milisekund";
	std::cout << "\nAlgorytm Bellmana-Forda: " << bellmana_forda / 1000 << " sekund, " << bellmana_forda % 1000 << " milisekund";
		std::cout << "\nUsprawniony Algorytm Bellmana-Forda: " << us_bellmana_forda / 1000 << " sekund, " << us_bellmana_forda % 1000 << " milisekund";
	std::cout << "\nAlgorytm Floyda-Warshalla: ";
	if (rozmiar < limit)
		std::cout << floyda_warshalla / 1000<< " sekund, " << floyda_warshalla % 1000 << " milisekund";
	else
		std::cout << "za dlugo zeby inne obliczenia byly przeprowadzone w rozsadnym czasie!";
	std::cout << "\nAlgorytm Kruskala: " << kruskala / 1000 << " sekund, " << kruskala % 1000 << " milisekund";
	std::cout << "\nAlgorytm Prima: " << prima / 1000 << " sekund, " << prima % 1000 << " milisekund";
	std::cout << "\nAlgorytm BFS: " << bsf / 1000 << " sekund, " << bsf % 1000 << " milisekund";
	std::cout << "\nAlgorytm DFS: " << dsf / 1000 << " sekund, " << dsf % 1000 << " milisekund";
	std::cin.ignore();
	getchar();
	system("cls");
}

void Menu::Glowne(){
	bool test = true;
	MenuBadaniaSkierowanego badSkier;
	MenuBadaniaNieSkierowanego badNieSkier;
	while (test){
		wyswietlTekst({
			"Witaj w programie o algorytmach grafowych!",
			"Postepuj wedlug instukcji pojawiajacych sie na ekranie.",
			"Na poczatek, wybierz jedna z opcji:",
			"a) Grafy Skierowane",
			"b) Grafy Nieskierowane",
			"c) Badanie czasu algorytmow"
		});
		char wybor;
		std::string znaki;
		std::cin >> znaki;
		wybor = znaki[0];
		switch(wybor){
		case 'a':
		case 'A':
			system("cls");
			badSkier.menu();
			break;
		case 'b':
		case 'B':
			system("cls");
			badNieSkier.menu();
			break;
		case 'c':
		case 'C':
			system("cls");
			pomiarCzasu();
			break;
		default:
			system("cls");
			wyswietlTekst({
				"Czy na pewno chcesz wyjsc z programu?",
				"Y/N?"
			});
			std::cin >> znaki;
			wybor = znaki[0];
			switch (wybor){
			case 'n':
			case 'N':
				test = true;
				system("cls");
				break;
			default:
				test = false;
				break;
			}
			break;
		}
	}
}
