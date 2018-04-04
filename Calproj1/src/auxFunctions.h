#ifndef AUX_H_
#define AUX_H_


#include <vector>
#include <string>
#include "Destino.h"
#include "Data.h"

using namespace std;

bool isBissexto(int ano);

int numDias(int mes, int ano);

Destino getDestinoByName(const vector<Destino> vec, string name);

vector<Data*> criaDatas(string d1, string d2);

string dataFinal(string dataInicio, int duration);

string maxPossibleStartDate(int noites, string maxDataFinal);

#endif
