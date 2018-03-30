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

const Data Alojamento::getDataFim() const {
	return dataFim;
}

void Alojamento::setDataFim(Data dataFim) {
	this->dataFim = dataFim;
}

const Data Alojamento::getDataInicio() const {
	return dataInicio;
}

void Alojamento::setDataInicio(Data dataInicio) {
	this->dataInicio = dataInicio;
}

Alojamento::~Alojamento() {
}

ostream& operator<<(ostream& out, const Alojamento &a) {
	out << "Cidade " << a.getCidade() << endl;
	out << "DataInicio: " << a.getDataInicio()<< endl;
	out << "DataFim: " << a.getDataFim() << endl;
	out << "Custo " << a.getCusto() << endl;

	return out;
}


