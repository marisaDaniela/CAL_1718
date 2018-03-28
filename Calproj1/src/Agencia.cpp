/*
 * Agencia.cpp
 *
 */

#include "Agencia.h"

void Agencia::leFicheiroAlojamentos() {
	string line;
	ifstream ficheiro;
	string cidade, dataInicio, dataFim, custoS;
	double custo;

	ficheiro.open("alojamentos.csv");
	if(!ficheiro) {
		cout << "Error opening file!"<<endl;
		return;
	}

	while (getline(ficheiro, line)) {
			istringstream i2;
			i2.str(line);
			getline(i2, cidade, ',');
			getline(i2, dataInicio, ',');
			getline(i2, dataFim, ',');
			getline(i2, custoS, ',');

			Data d1(dataInicio);
			Data d2(dataFim);
			custo = atof(custoS.c_str());

			Alojamento *a = new Alojamento(cidade, d1, d2, custo);
			alojamentos.push_back(a);
	}

}

void Agencia::verAlojamentos() {
		vector<Alojamento *> a = alojamentos;
		for (int i = 0; i < a.size(); i++)
		{
			cout << *(a[i]) << endl;
		}
	}
