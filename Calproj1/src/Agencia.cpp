/*
 * Agencia.cpp
 *
 */

#include "Agencia.h"

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

	if(cidade == "amesterdao")
	{
		for(int i = 0; i < amesterdao.size(); i++)
		{
			if(data1 == amesterdao[i]->dataInicio) { // TODO: tratar dos meses e anos diferetes
				if((amesterdao[i]->getDataFim().getDia()) == (amesterdao[i]->getDataInicio().getDia() + dias))
				{
					cout << "Amesterdao: o custo sera de:" << amesterdao[i]->getCusto() << " € " << endl;
				}
				else
				{
					cout << "Nao existem voos disponiveis para o periodo de tempo requirido!" << endl;
				}
			}
		}
	}
	else if(cidade == "berlim")
	{
		for(int i = 0; i < berlim.size(); i++)
		{
			if(data1 == berlim[i]->dataInicio) {
				if((berlim[i]->getDataFim().getDia()) == (berlim[i]->getDataInicio().getDia() + dias))
				{
					cout << "Berlim: o custo sera de:" << berlim[i]->getCusto() << " € " << endl;
				}
				else
				{
					cout << "Nao existem voos disponiveis para o periodo de tempo requirido!" << endl;
				}
			}
		}
	}
	else if(cidade == "bruxelas")
	{
		for(int i = 0; i < bruxelas.size(); i++)
		{
			if(data1 == bruxelas[i]->dataInicio) {
				if((bruxelas[i]->getDataFim().getDia()) == (bruxelas[i]->getDataInicio().getDia() + dias))
				{
					cout << "Bruxelas: o custo sera de:" << bruxelas[i]->getCusto() << " € " << endl;
				}
				else
				{
					cout << "Nao existem voos disponiveis para o periodo de tempo requirido!" << endl;
				}
			}
		}
	}
	else if(cidade == "lisboa")
	{
		for(int i = 0; i < lisboa.size(); i++)
		{
			if(data1 == lisboa[i]->dataInicio) {
				if((lisboa[i]->getDataFim().getDia()) == (lisboa[i]->getDataInicio().getDia() + dias))
				{
					cout << "Lisboa: o custo sera de:" << lisboa[i]->getCusto() << " € " << endl;
				}
				else
				{
					cout << "Nao existem voos disponiveis para o periodo de tempo requirido!" << endl;
				}
			}
		}
	}
	else if(cidade == "madrid")
	{
		for(int i = 0; i < madrid.size(); i++)
		{
			if(data1 == madrid[i]->dataInicio) {
				if((lisboa[i]->getDataFim().getDia()) == (madrid[i]->getDataInicio().getDia() + dias))
				{
					cout << "Madrid: o custo sera de:" << madrid[i]->getCusto() << " € " << endl;
				}
				else
				{
					cout << "Nao existem voos disponiveis para o periodo de tempo requirido!" << endl;
				}
			}
		}
	}
	else if(cidade == "paris")
	{
		for(int i = 0; i < paris.size(); i++)
		{
			if(data1 == paris[i]->dataInicio) {
				if((paris[i]->getDataFim().getDia()) == (paris[i]->getDataInicio().getDia() + dias))
				{
					cout << "Paris: o custo sera de:" << paris[i]->getCusto() << " € " << endl;
				}
				else
				{
					cout << "Nao existem voos disponiveis para o periodo de tempo requirido!" << endl;
				}
			}
		}
	}

	else if(cidade == "praga")
	{
		for(int i = 0; i < praga.size(); i++)
		{
			if(data1 == praga[i]->dataInicio) {
				if((praga[i]->getDataFim().getDia()) == (praga[i]->getDataInicio().getDia() + dias))
				{
					cout << "Praga: o custo sera de:" << praga[i]->getCusto() << " € " << endl;
				}
				else
				{
					cout << "Nao existem voos disponiveis para o periodo de tempo requirido!" << endl;
				}
			}
		}
	}
}
