/*
 * Alojamento.cpp
 *
 */

#include "Alojamento.h"

Alojamento::Alojamento(string cidade, double custo) {
	setCidade(cidade);
	setCusto(custo);
}

string Alojamento::getCidade() const {
	return cidade;
}

void Alojamento::setCidade(string cidade) {
	this->cidade = cidade;;
}

double Alojamento::getCusto() const {
	return custo;
}

void Alojamento::setCusto(double custo) {
	this->custo = custo;
}

Alojamento::~Alojamento() {
}

vector<Data*> Alojamento::getDatas() const {
	return datas;
}

void Alojamento::criaDatas(string d1, string d2) {
	Data dataInicio = Data(d1);
	Data dataFim = Data(d2);

	int dia = dataInicio.getDia();
	int mes = dataInicio.getMes();
	int num = numDias(mes, dataInicio.getAno());

	bool stop = false;

	while(!stop)
	{
		Data *d1 = new Data(dia, mes, dataInicio.getAno());
		datas.push_back(d1);
		if(stop)
			break;
		if(dia==dataFim.getDia() && mes==dataFim.getMes())
			stop = true;
		if(dia == num) {
			dia = 0;
			if(mes < 12)
				mes++;
			else
				mes = 1;
			num = numDias(mes, dataInicio.getAno());
		}
		dia++;
	}
}

void Alojamento::showDatas() {
	for(int i = 0; i < datas.size(); i++ ){
		cout << datas[i]->getDia() <<"/" << datas[i]->getMes() <<"/" << datas[i]->getAno() << endl;
	}
}

ostream& operator<<(ostream& out, const Alojamento &a) {
	out << "Cidade " << a.getCidade() << endl;
	out << "Custo " << a.getCusto() << endl;

	return out;
}


