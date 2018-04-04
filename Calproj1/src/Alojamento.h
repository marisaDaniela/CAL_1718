/*
 * Alojamento.h
 *
 */

#include "Data.h"
#include "auxFunctions.h"
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Alojamento {
	string cidade;
	double custo;
public:
	Data dataInicio;
	Data dataFim;
	vector<Data*> datas;

	Alojamento(){}
	Alojamento(string cidade, Data dataInicio, Data dataFim, double custo);
	virtual ~Alojamento();

	string getCidade() const;
	void setCidade(string cidade);

	double getCusto() const;
	void setCusto(double custo);

	Data getDataFim() const;
	void setDataFim(Data dataFim);

	Data getDataInicio() const;
	void setDataInicio(Data dataInicio);

	void criaDatas(string dataInicio, string dataFim);
	void showDatas();

	vector<Data*> getDatas() const;

	void leFicheiroAlojamentos();

	friend ostream& operator<<(ostream& out, const Alojamento &a);
};
