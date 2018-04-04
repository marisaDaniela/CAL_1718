#include "auxFunctions.h"


bool isBissexto(int ano) {
		if(((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0))
			return true;
			else
				return false;
	}

int numDias(int mes, int ano){
	int num = 0;
	switch(mes){
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		num = 31;
		break;
	case 2:
		if(isBissexto(ano))
			num = 29;
		else num = 28;
		break;
	default:
		num = 30;
	}
	return num;
}

Destino getDestinoByName(const vector<Destino> vec, string name){
	Destino dest;
	dest.getName() = "";
	for(auto d:vec){
		if(d.getName()==name){
			dest = d;
			break;
		}
	}
	return dest;
}
