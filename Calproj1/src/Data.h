/*
 * Data.h
 */
#include <string>

using namespace std;

class Data {
	int dia, mes, ano;
	string dataString;
public:
	Data(){};
	Data(int dia, int mes, int ano);
	virtual ~Data();
	Data(string data); // data na forma DD/MM/AAA

	int getAno() const;
	void setAno(int ano);

	int getDia() const;
	void setDia(int dia);

	int getMes() const;
	void setMes(int mes);

	string getDataString() const;
	void setDataString(string data);

	bool operator==(Data& rhs) const;
	friend ostream& operator<<(ostream& out, const Data &d);

};

