/*
 * Data.cpp
 */

#include "Data.h"

Data::Data(int dia, int mes, int ano) {
	this->ano=ano;
	this->mes=mes;
	this->dia=dia;
}

Data::Data(string dataStr) {
	dia = stoi(dataStr.substr(0, 2));
	mes = stoi(dataStr.substr(3, 4));
	ano = stoi(dataStr.substr(6, 9));
	setDataString(dataStr);
}

Data::~Data() {

}

int Data::getAno() const {
	return ano;
}

void Data::setAno(int ano) {
	this->ano = ano;
}

int Data::getDia() const {
	return dia;
}

void Data::setDia(int dia) {
	this->dia = dia;
}

int Data::getMes() const {
	return mes;
}

void Data::setMes(int mes) {
	this->mes = mes;
}

string Data::getDataString() const {
	return dataString;
}

void Data::setDataString(string data) {
	this->dataString = data;
}

ostream& operator<<(ostream& out, const Data & data)
{
	out << data.getDataString();
	return out;
}

bool Data::operator==(Data& rhs) const {
	if ((this->dia == rhs.dia) && (this->mes == rhs.mes) && (this->ano == rhs.ano))
		return true;
	return false;
}


