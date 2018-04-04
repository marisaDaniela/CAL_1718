/*
 * Alojamento.h
 *
 */

#include <iostream>
#include <sstream>
#include "Data.h"
#include "auxFunctions.h"

class Alojamento {
	string cidade;
	double custo;
public:
	vector<Data*> datas;

	Alojamento(string cidade,  double custo);
	virtual ~Alojamento();

	string getCidade() const;
	void setCidade(string cidade);

	double getCusto() const;
	void setCusto(double custo);

	void criaDatas(string dataInicio, string dataFim);
	void showDatas();

	vector<Data*> getDatas() const;

	friend ostream& operator<<(ostream& out, const Alojamento &a);
};
