#include "Destino.h"

Destino::Destino(string n, double a): name(n), custo_aloj(a) {}
Destino::Destino(){}

string Destino::getName() const {
	return name;
}

double Destino::getCustoAloj() const {
	return custo_aloj;
}

bool Destino::operator == (const Destino &d2) const {
	return (name==d2.name && custo_aloj==d2.custo_aloj);
}

vector<string> Destino::getPontosInteresse() const {
	return pontos_interesse;
}

void Destino::setPontosInteresse(vector<string> pontosInteresse) {
	pontos_interesse = pontosInteresse;
}
