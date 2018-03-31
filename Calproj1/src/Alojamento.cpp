/*
 * Alojamento.cpp
 *
 */

#include "Alojamento.h"

Alojamento::Alojamento(string cidade, Data dataInicio, Data dataFim, double custo) {
	this->cidade = cidade;
	this->dataInicio = dataInicio;
	this->dataFim = dataFim;
	this->custo = custo;
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

Data Alojamento::getDataFim() const {
	return dataFim;
}

void Alojamento::setDataFim(Data dataFim) {
	this->dataFim = dataFim;
}

Data Alojamento::getDataInicio() const {
	return dataInicio;
}

void Alojamento::setDataInicio(Data dataInicio) {
	this->dataInicio = dataInicio;
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

	while(mes<dataFim.getMes() || dia <= dataFim.getDia())
	{
		Data *d1 = new Data(dia, mes, dataInicio.getAno());
		datas.push_back(d1);
		if(dia == num) {
			dia = 0;
			if(mes < 12){
				mes++;
				num = numDias(mes, dataInicio.getAno());
			}
		}
		dia++;
	}
	showDatas();
}

void Alojamento::showDatas() {
	for(int i = 0; i < datas.size(); i++ ){
		cout << datas[i]->getDia() <<"/" << datas[i]->getMes() <<"/" << datas[i]->getAno() << endl;
	}
}
ostream& operator<<(ostream& out, const Alojamento &a) {
	out << "Cidade " << a.getCidade() << endl;
	out << "DataInicio: " << a.getDataInicio()<< endl;
	out << "DataFim: " << a.getDataFim() << endl;
	out << "Custo " << a.getCusto() << endl;

	return out;
}


