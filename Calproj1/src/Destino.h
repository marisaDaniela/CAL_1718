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
	Destino ();
	string getName() const;
	double getCustoAloj() const;
	bool operator == (const Destino &d2) const;
	//friend ostream & operator << (ostream &os, Destino &d);
};


