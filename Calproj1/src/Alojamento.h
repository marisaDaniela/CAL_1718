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

	// ---------------------------------------------------------------------------

	bool isBissexto(int ano) {
		if(((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0))
			return true;
			else
				return false;
	}

	int numDias(int mes, int ano){
		int num = 0;
		switch(mes){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			num = 31;
			break;
		case 2:
			if(isBissexto(ano))
				num = 29;
			else num = 28;
			break;
		default:
			num = 30;
		}
		return num;
	}
	// ---------------------------------------------------------------------------

};
