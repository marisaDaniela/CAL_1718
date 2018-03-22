#include "Destino.h"

Destino::Destino(string n, double a): name(n), custo_aloj(a) {}

string Destino::getName() const {
	return name;
}

double Destino::getCustoAloj() const {
	return custo_aloj;
}

/*bool Person::operator == (const Person &p2) const {
	return (name==p2.name && age==p2.age);
}*/

/*ostream & operator << (ostream &os, Destino &d) {
   os << d.getName();
   return os;
}*/
