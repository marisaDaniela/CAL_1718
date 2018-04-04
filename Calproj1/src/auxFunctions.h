#ifndef AUX_H_
#define AUX_H_


#include <vector>
#include <string>
#include "Destino.h"

using namespace std;

bool isBissexto(int ano);

int numDias(int mes, int ano);

Destino getDestinoByName(const vector<Destino> vec, string name);

#endif
