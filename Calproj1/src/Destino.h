/*
 * Person.h
 */


#include <string>
using namespace std;

class Destino{
	string name;
	double custo_aloj;
public:
	Destino (string n, double a);
	string getName() const;
	double getCustoAloj() const;
	//bool operator == (const Person &p2) const;
	//friend ostream & operator << (ostream &os, Destino &d);
};


