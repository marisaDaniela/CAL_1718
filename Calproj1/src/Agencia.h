/*
 * Agencia.h
 *
 */

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

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
public:
	void leFicheiroAlojamentos(string nomeCidade);
	void verAlojamentos(string nomeCidade);

	/**
	 *  Função que retorna o custo a partir do dia x (passado por argumento) durante
	 *  y dias (passado por argumento) para uma determinada cidade (passado por argumento)
	 */
	double getCustoTempo(string data, int dias, string cidade);
};

