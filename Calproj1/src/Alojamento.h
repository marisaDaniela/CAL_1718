/*
 * Alojamento.h
 *
 */

#include "Data.h"
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Alojamento {
	string cidade;
	double custo;
public:
	Data dataInicio;
	Data dataFim;
	Alojamento(string cidade, Data dataInicio, Data dataFim, double custo);
	virtual ~Alojamento();

	string getCidade() const;
	void setCidade(string cidade);

	double getCusto() const;
	void setCusto(double custo);

	const Data getDataFim() const;
	void setDataFim(Data dataFim);

	const Data getDataInicio() const;
	void setDataInicio(Data dataInicio);

	void leFicheiroAlojamentos();

	friend ostream& operator<<(ostream& out, const Alojamento &a);


};
