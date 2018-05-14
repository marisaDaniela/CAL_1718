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

vector<Data*> criaDatas(string d1, string d2) {
	vector<Data*> datas;
	Data dataInicio = Data(d1);
	Data dataFim = Data(d2);

	int dia = dataInicio.getDia();
	int mes = dataInicio.getMes();
	int num = numDias(mes, dataInicio.getAno());

	bool stop = false;


	while(!stop){
		Data *d1 = new Data(dia, mes, dataInicio.getAno());
		datas.push_back(d1);
		if(stop)
			break;
		if(dia==dataFim.getDia() && mes==dataFim.getMes())
			stop = true;
		if(dia == num) {
			dia = 0;
			if(mes < 12)
				mes++;
			else
				mes = 1;
			num = numDias(mes, dataInicio.getAno());

		}
		dia++;
	}
	return datas;
}

string dataFinal(string dataInicio, int duration){
	Data d = Data(dataInicio);

	int diasMes = numDias(d.getMes(),d.getAno());
	int result = d.getDia()+duration;
	if(result>diasMes){
		result -= diasMes;
		int mes = d.getMes()+1;
		d.setMes(mes);
	}

	d.buildString(result,d.getMes(),d.getAno());

	return d.getDataString();
}

string maxPossibleStartDate(int noites, string maxDataFinal){
	Data d = Data(maxDataFinal);

	int diasMes = numDias(d.getMes()-1,d.getAno());
	int result = d.getDia()-noites;
	if(result<=0){
		result = diasMes + result;
		int mes = d.getMes()-1;
		d.setMes(mes);
	}

	d.buildString(result,d.getMes(),d.getAno());

	return d.getDataString();
}

void readInputInt(int &x, string message){
	int tmp;
	bool added = false;
	while(!added){
		while(!(cin >> tmp)){
				cout << "Bad value! Must be an integer > 0! "<< message;
				cin.clear();
				cin.ignore();
		}
		if(tmp>0)
			added = true;
		else
			cout << "Bad value! Must be an integer > 0! "<< message;
	}
	x = tmp;
}

void readInputDate(string &date, string message){

	string tmp;
	bool valid = false;
	while(!valid){
		cin >> tmp;
		Data d = Data(tmp);
		if(d.getDia()> numDias(d.getMes(),d.getAno()) || d.getDia()<1 || d.getMes()>12 || d.getMes()<1 || d.getAno()!=2018){
			cout << "Bad value! Must be a valid date of the year 2018. "<< message;
		}
		else
			valid = true;
	}
	date = tmp;
}


bool isValidDate(string date1, string date2){
	Data d1 = Data(date1);
	Data d2 = Data(date2);
	return !(d1>d2);
}

/**
 * Converts any lower case letter of a string in upper case letters.
 * @Param word - the string to be converted
 */
void stringToUpper(string &word){
	for(size_t i=0; i < word.length(); i++)
		word.at(i) = toupper(word.at(i));
}
