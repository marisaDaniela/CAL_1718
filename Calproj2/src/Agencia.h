#ifndef AGENCIA_H_
#define AGENCIA_H_


#include <fstream>
#include <map>
#include <set>
#include "Alojamento.h"
#include "auxFunctions.h"

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
	map<string,set<string> > pontosInteresse;

	void leFicheiroAlojamentos(string nomeCidade);
	void lerPontosDeInteresse();
	string chopString(string &buf, string delimiter);
	vector<Alojamento *> getCityVector(string nomeCidade) const;
	int editDistance(string pattern, string text);
	void pre_kmp(string pattern, vector<int> & prefix);
	int kmp(string text, string pattern);
public:
	void pesquisaAproximada(string word, vector<string> &matches, vector<string> &paises);
	void leFicheiros();
	void verAlojamentos(string nomeCidade);
	double getCustoTempo(string data, int dias, string cidade);
	bool pesquisaExata(string name, vector<string> &matches, vector<string> &paises);

};

#endif

