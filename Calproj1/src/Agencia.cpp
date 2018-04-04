/*
 * Agencia.cpp
 *
 */

#include "Agencia.h"

void Agencia::leFicheiros(){
	leFicheiroAlojamentos("lisboa");
	leFicheiroAlojamentos("berlim");
	leFicheiroAlojamentos("bruxelas");
	leFicheiroAlojamentos("madrid");
	leFicheiroAlojamentos("amesterdao");
	leFicheiroAlojamentos("paris");
	leFicheiroAlojamentos("praga");
}

void Agencia::leFicheiroAlojamentos(string nomeCidade) {
	string line;
	ifstream ficheiro;
	string cidade, dataInicio, dataFim, custoS;
	double custo;
	string filename = "paises/" + nomeCidade + ".csv";
	ficheiro.open(filename);
	if(!ficheiro) {
		cout << "Error opening file!"<<endl;
		return;
	}

	while (getline(ficheiro, line)) {
		istringstream i2;
		i2.str(line);
		getline(i2, cidade, ',');
		getline(i2, dataInicio, ',');
		getline(i2, dataFim, ',');
		getline(i2, custoS, ',');

		custo = atof(custoS.c_str());

		Alojamento *a = new Alojamento(cidade, custo);
		a->criaDatas(dataInicio,dataFim);

		if(nomeCidade == "amesterdao")
			amesterdao.push_back(a);
		else if(nomeCidade == "berlim")
			berlim.push_back(a);
		else if(nomeCidade == "bruxelas")
			bruxelas.push_back(a);
		else if(nomeCidade == "lisboa")
			lisboa.push_back(a);
		else if(nomeCidade == "madrid")
			madrid.push_back(a);
		else if(nomeCidade == "paris")
			paris.push_back(a);
		else if(nomeCidade == "praga")
			praga.push_back(a);
	}

}

vector<Alojamento *> Agencia::getCityVector(string nomeCidade) const{
	vector<Alojamento *> a;
	if(nomeCidade == "Amesterdao")
		a = amesterdao;
	else if(nomeCidade == "Berlim")
		a = berlim;
	else if(nomeCidade == "Bruxelas")
		a = bruxelas;
	else if(nomeCidade == "Lisboa")
		a = lisboa;
	else if(nomeCidade == "Madrid")
		a = madrid;
	else if(nomeCidade == "Paris")
		a = paris;
	else if(nomeCidade == "Praga")
		a = praga;
	return a;
}

void Agencia::verAlojamentos(string nomeCidade) {
	vector<Alojamento *> a = getCityVector(nomeCidade);

	for (int i = 0; i < a.size(); i++)
		cout << *(a[i]) << endl;
}


double Agencia::getCustoTempo(string data, int dias, string cidade) {
	Data data1(data);

	double custo = 0;
	int daysleft = 0;
	bool start = false;

	vector<Alojamento *> city = getCityVector(cidade);

	bool done = false;

	for(int i=0; i<city.size();i++){
		for(auto data : city[i]->getDatas()){
			if(data1.getDia()==data->getDia() && data1.getMes()==data->getMes() && data1.getAno()==data->getAno()){
				daysleft = dias;
				start = true;
			}
			if(start){
				daysleft--;
				custo += city[i]->getCusto();
				if(daysleft==0){
					done = true;
					break;
				}
			}
		}
		if(done)
			break;
	}

	return custo;
}
