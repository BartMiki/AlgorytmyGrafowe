#include "stdafx.h"
#include "Rysuj.h"
#include <string>

Punkt Rysuj::obliczWystapienie(Punkt poczatek, Punkt koniec){
	Punkt wystapienie;
	wystapienie.ustaw((koniec.x + poczatek.x) / 2, (koniec.y + poczatek.y) / 2);
	return wystapienie;
}

Rysuj::Rysuj() {
	czcionka = new sf::Font;
	czcionka->loadFromFile("arial.ttf");

	tablicaKolorow.push_back(sf::Color(255, 0, 0)); //czerwony
	tablicaKolorow.push_back(sf::Color(0, 85, 255)); //niebieski
	tablicaKolorow.push_back(sf::Color(55, 255, 0)); //zielony
	tablicaKolorow.push_back(sf::Color(255, 212, 0)); //zolty
	tablicaKolorow.push_back(sf::Color(255, 92, 0)); //pomaranczowy

	tablicaKolorow.push_back(sf::Color(0, 199, 255)); //blekit
	tablicaKolorow.push_back(sf::Color(255, 0, 84)); //malina
	tablicaKolorow.push_back(sf::Color(0, 255, 80)); //szmaragdowy
	tablicaKolorow.push_back(sf::Color(195, 255, 0)); //limonkowy
	tablicaKolorow.push_back(sf::Color(220, 0, 255)); //magneta

	tablicaKolorow.push_back(sf::Color(170, 162, 0)); //zloty
	tablicaKolorow.push_back(sf::Color(0, 255, 169)); //morski
	tablicaKolorow.push_back(sf::Color(131, 0, 255)); //fiolet
	tablicaKolorow.push_back(sf::Color(150, 0, 0)); //buraczkowy
	tablicaKolorow.push_back(sf::Color(255, 0, 187)); //roz

}
Rysuj::~Rysuj() {
	delete czcionka;
}
void Rysuj::Linie(Punkt poczatek, Punkt koniec, sf::RenderWindow & okno, sf::Color kolor){
	sf::Vertex linia[2] = {
		sf::Vertex(sf::Vector2f(poczatek.x,poczatek.y)),
		sf::Vertex(sf::Vector2f(koniec.x, koniec.y))
	};
	linia[0].color = kolor;
	linia[1].color = kolor;
	okno.draw(linia, 2, sf::Lines);
}

void Rysuj::Strzalke(Punkt poczatek, Punkt koniec,
	int waga, sf::RenderWindow &okno, sf::Color kolor) {
	sf::Vertex linia[2] = {
		sf::Vertex(sf::Vector2f(poczatek.x,poczatek.y)),
		sf::Vertex(sf::Vector2f(koniec.x, koniec.y))
	};
	linia[0].color = kolor;
	linia[1].color = kolor;

	//obliczmy kat w radianach
	float kat = std::atan((koniec.y - poczatek.y) / (koniec.x - poczatek.x));
	//w stopniach
	kat = kat*180.0 / 3.1416;
	sf::CircleShape trojkat(10, 3);
	//ustawiamy trojkat
	trojkat.setOrigin(10, -promienWierzcholka);
	if (koniec.x<poczatek.x)
		trojkat.setRotation(-90);
	else
		trojkat.setRotation(90);
	trojkat.rotate(kat);
	trojkat.setPosition(koniec.x, koniec.y);
	trojkat.setFillColor(kolor);
	//numerek
	sf::Text numerek;
	numerek.setFont(*czcionka);
	numerek.setFillColor(sf::Color::Black);
	numerek.setOutlineColor(kolor);
	numerek.setOutlineThickness(3);
	numerek.setCharacterSize(promienWierzcholka);
	numerek.setString(std::to_string(waga));
	sf::FloatRect wymiaryNumerka = numerek.getLocalBounds();
	float x, y;
	x = wymiaryNumerka.width * 2 / 3;
	y = wymiaryNumerka.height * 2 / 3;
	numerek.setOrigin(x, y);
	numerek.setPosition(poczatek.x, poczatek.y);
	//
	okno.draw(linia, 2, sf::Lines);
	okno.draw(trojkat);
	if(waga!=0)
		okno.draw(numerek);
}

void Rysuj::odwroconaStrzalke(Punkt poczatek, Punkt koniec, sf::RenderWindow & okno, sf::Color kolor){
	sf::Vertex linia[2] = {
		sf::Vertex(sf::Vector2f(poczatek.x,poczatek.y)),
		sf::Vertex(sf::Vector2f(koniec.x, koniec.y))
	};
	linia[0].color = kolor;
	linia[1].color = kolor;

	//obliczmy kat w radianach
	float kat = std::atan((koniec.y - poczatek.y) / (koniec.x - poczatek.x));
	//w stopniach
	kat = kat*180.0 / 3.1416;
	sf::CircleShape trojkat(10, 3);
	//ustawiamy trojkat
	trojkat.setOrigin(10, (promienWierzcholka*2)+10);
	if (koniec.x<poczatek.x)
		trojkat.setRotation(-90);
	else
		trojkat.setRotation(90);
	trojkat.rotate(kat);
	trojkat.setPosition(poczatek.x, poczatek.y);
	trojkat.setFillColor(kolor);
	//
	okno.draw(linia, 2, sf::Lines);
	okno.draw(trojkat);
}

void Rysuj::PolaczenieSkierowanego(Punkt poczatek, Punkt koniec, int waga, sf::RenderWindow & okno, sf::Color kolor){
	Punkt srodek[3];
	srodek[0] = obliczWystapienie(poczatek, koniec);
	srodek[1] = obliczWystapienie(srodek[0], koniec);
	srodek[2] = obliczWystapienie(poczatek, srodek[0]);
	odwroconaStrzalke(poczatek, srodek[0], okno, kolor);
	Linie(srodek[0], srodek[1], okno, kolor);
	Strzalke(srodek[1], koniec, waga, okno, kolor);
}

void Rysuj::PolaczenieNieskierowanego(Punkt poczatek, Punkt koniec, int waga, sf::RenderWindow & okno, sf::Color kolor){
	Linie(poczatek, koniec, okno, kolor);
	Punkt srodek[3];
	srodek[0] = obliczWystapienie(poczatek, koniec);
	srodek[1] = obliczWystapienie(srodek[0], koniec);
	Linie(poczatek, koniec, okno, kolor);
	sf::Text numerek;
	numerek.setFont(*czcionka);
	numerek.setFillColor(sf::Color::Black);
	numerek.setOutlineColor(kolor);
	numerek.setOutlineThickness(3);
	numerek.setCharacterSize(promienWierzcholka);
	numerek.setString(std::to_string(waga));
	sf::FloatRect wymiaryNumerka = numerek.getLocalBounds();
	float x, y;
	x = wymiaryNumerka.width * 2 / 3;
	y = wymiaryNumerka.height * 2 / 3;
	numerek.setOrigin(x, y);
	numerek.setPosition(srodek[1].x, srodek[1].y);
	okno.draw(numerek);
}

void Rysuj::Wierzcholek(Punkt lokacja, sf::RenderWindow & okno,
	sf::Color kolor, sf::Color wypelnienie)
{
	sf::CircleShape wierzcholek(promienWierzcholka);
	wierzcholek.setOutlineColor(kolor);
	wierzcholek.setOutlineThickness(promienWierzcholka/10);
	wierzcholek.setFillColor(wypelnienie);
	wierzcholek.setOrigin(promienWierzcholka, promienWierzcholka);
	wierzcholek.setPosition(lokacja.x, lokacja.y);
	sf::Text numerek;
	numerek.setFont(*czcionka);
	numerek.setFillColor(kolor);
	numerek.setCharacterSize(promienWierzcholka);
	numerek.setString(std::to_string(lokacja.indeks));
	sf::FloatRect wymiaryNumerka = numerek.getLocalBounds();
	float x, y;
	x = wymiaryNumerka.width*2/3;
	y = wymiaryNumerka.height*2/3;
	numerek.setOrigin(x,y);
	numerek.setPosition(lokacja.x, lokacja.y);
	//rysowanie
	okno.draw(wierzcholek);
	okno.draw(numerek);
}
