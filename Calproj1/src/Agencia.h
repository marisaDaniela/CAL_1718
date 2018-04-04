#ifndef AGENCIA_H_
#define AGENCIA_H_


#include <fstream>
#include "Alojamento.h"

using namespace std;

class Agencia {
	vector<Alojamento *> alojamentos;
	vector<Alojamento *> amesterdao;
	vector<Alojamento *> berlim;
	vector<Alojamento *> bruxelas;
	vector<Alojamento *> lisboa;
	vector<Alojamento *> madrid;
	vector<Alojamento *> paris;
	vector<Alojamento *> praga;

	void leFicheiroAlojamentos(string nomeCidade);
	vector<Alojamento *> getCityVector(string nomeCidade) const;
public:
	void leFicheiros();
	void verAlojamentos(string nomeCidade);
	double getCustoTempo(string data, int dias, string cidade);
};

#endif

