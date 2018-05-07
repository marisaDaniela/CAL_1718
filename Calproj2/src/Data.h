/*
 * Data.h
 */

#ifndef DATA_H_
#define DATA_H_

#include <string>

using namespace std;

class Data {
	int dia, mes, ano;
	string dataString;

	int getValue(string &dataStr);
public:
	Data(int dia, int mes, int ano);
	virtual ~Data();
	Data(string data); // data na forma DD/MM/AAA

	void buildString(int dia, int mes, int ano);

	int getAno() const;
	void setAno(int ano);

	int getDia() const;
	void setDia(int dia);

	int getMes() const;
	void setMes(int mes);

	string getDataString() const;
	void setDataString(string data);

	bool operator == (Data &rhs) const;
	bool operator > (Data &rhs) const;
	friend ostream& operator<<(ostream& out, const Data &d);

};

#endif
