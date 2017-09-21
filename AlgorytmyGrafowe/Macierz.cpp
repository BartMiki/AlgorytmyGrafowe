#include "stdafx.h"
#include "Macierz.h"

void Macierz::utworzMacierz(int n) {
	rozmiar = n;
	std::vector<int> wiersz;
	wiersz.resize(n);
	for (int i = 0; i < rozmiar; i++) {
		macierz.push_back(wiersz);
	}
}
void Macierz::setMacierz(int value, int i = 0, int j = 0) {
	macierz[i][j] = value;
}
void Macierz::setMacierz(std::vector<std::vector<int>> m) {
	macierz = m;
}
int Macierz::getMacierz(int i, int j) {
	return macierz[i][j];
}
std::vector<std::vector<int>> Macierz::getMacierz() {
	return macierz;
}

std::vector<int> & Macierz::operator[](int i){
	return macierz[i];
}
