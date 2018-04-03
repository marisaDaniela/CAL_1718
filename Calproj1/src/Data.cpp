/*
 * Data.cpp
 */

#include "Data.h"



Data::Data(int dia, int mes, int ano) {
	this->ano=ano;
	this->mes=mes;
	this->dia=dia;
	buildString();
}

Data::Data(string dataStr) {
	setDataString(dataStr);
	string delimiter = "/";
	size_t pos = dataStr.find(delimiter);
	dia = stoi(dataStr.substr(0, pos));
	dataStr.erase(0, pos+1);
	pos = dataStr.find(delimiter);
	mes = stoi(dataStr.substr(0, pos));
	dataStr.erase(0, pos+1);
	pos = dataStr.find(delimiter);
	ano = stoi(dataStr.substr(0, pos));
	dataStr.erase(0, pos+1);
}

Data::~Data() {

}

void Data::buildString(){
	string s = to_string(dia);
	s += "/";
	s += to_string(mes);
	s += "/";
	s += to_string(ano);
	setDataString(s);
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

bool Data::operator == (Data &rhs) const {
	return (dia==rhs.dia && mes==rhs.mes && ano==rhs.ano);
}

bool Data::operator > (Data &rhs) const{
	return (ano>rhs.ano || mes>rhs.mes || (dia>rhs.dia && mes==rhs.mes));
}

