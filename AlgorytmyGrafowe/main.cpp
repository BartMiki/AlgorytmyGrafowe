
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include "Menu.h"

void test();

int main(){
	//test();
	Menu menu;
	menu.Glowne();
}

void test() {
	int n,p,k;
	std::cin >> n;
	Skierowany graf(n);
	std::cin >> n;
	graf.Gnp(n);
	graf.losujWagi();
	graf.wyswietlTalice();
	graf.Graf::wyswietlGraf();
	std::cout << "\nPodaj poczatkowy indeks:\n";
	std::cin >> p;
	ParaTablic tablice;
	graf.algorytmBellmanaForda(p,tablice);
	std::cout << "\nPodaj koncowy indeks:\n";
	std::cin >> k;
	graf.wysietlSciezke(k, tablice);
}
