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

		Data d1(dataInicio);
		Data d2(dataFim);
		custo = atof(custoS.c_str());

		Alojamento *a = new Alojamento(cidade, d1, d2, custo);
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

void Agencia::verAlojamentos(string nomeCidade) {
	vector<Alojamento *> a;
	if(nomeCidade == "amesterdao")
		a = amesterdao;
	else if(nomeCidade == "berlim")
		a = berlim;
	else if(nomeCidade == "bruxelas")
		a = bruxelas;
	else if(nomeCidade == "lisboa")
		a = lisboa;
	else if(nomeCidade == "madrid")
		a = madrid;
	else if(nomeCidade == "paris")
		a = paris;
	else if(nomeCidade == "praga")
		a = praga;

	for (int i = 0; i < a.size(); i++)
	{
		cout << *(a[i]) << endl;
	}
}




double Agencia::getCustoTempo(string data, int dias, string cidade) {
	Data data1(data);

	double custo = 0;
	int daysleft = 0;
	bool start = false;
	vector<Alojamento *> city;

	if(cidade=="Amesterdao")
		city = amesterdao;
	else if(cidade=="Berlim")
		city = berlim;
	else if(cidade=="Bruxelas")
		city = bruxelas;
	else if(cidade=="Lisboa")
		city = lisboa;
	else if(cidade=="Madrid")
		city = madrid;
	else if(cidade=="Paris")
		city = paris;
	else if(cidade=="Praga")
		city = praga;

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
