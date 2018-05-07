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

void Alojamento::setDatas(vector<Data*> vec){
	this->datas = vec;
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


