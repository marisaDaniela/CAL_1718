#include "Destino.h"

Destino::Destino(string n, double a): name(n), custo_aloj(a) {}
Destino::Destino(){}

string Destino::getName() const {
	return name;
}

/*bool Person::operator == (const Person &p2) const {
	return (name==p2.name && age==p2.age);
}*/

ostream & operator << (ostream &os, Destino &d) {
   os << d.getName();
   return os;
}
