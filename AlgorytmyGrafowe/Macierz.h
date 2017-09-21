#ifndef Macierz_h
#define Macierz_h
#include <vector>

class Macierz {
	unsigned int rozmiar;
	std::vector<std::vector<int>> macierz;
public:
	void utworzMacierz(int n);
	void setMacierz(int value, int i, int j);
	void setMacierz(std::vector<std::vector<int>> m);
	int getMacierz(int i, int j);
	std::vector<std::vector<int>> getMacierz();
	std::vector<int>& operator[](int i);
};

#endif
