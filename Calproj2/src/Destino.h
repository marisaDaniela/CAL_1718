#include <string>
#include <vector>
using namespace std;

#ifndef DESTINO_H_
#define DESTINO_H_

class Destino{
	string name;
	double custo_aloj;
	vector<string> pontos_interesse;
public:
	Destino (string n, double a);
	Destino ();
	string getName() const;
	double getCustoAloj() const;
	bool operator == (const Destino &d2) const;

	vector<string> getPontosInteresse() const;
	void setPontosInteresse(vector<string> pontosInteresse);
};
#endif

