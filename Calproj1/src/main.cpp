#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Destino.h"
#include "Graph.h"

using namespace std;

Destino getDestinoByName(const vector<Destino> vec, string name){
	Destino dest;
	for(auto d:vec){
		if(d.getName()==name){
			dest = d;
			break;
		}
	}
	return dest;
}

int main(void) {
	ifstream ficheiro;
	Graph<Destino> myGraph;

	ficheiro.open("destinos.txt");
	if(!ficheiro){
		cout << "Error opening file!"<<endl;
		return -1;
	}

	vector<Destino> destinos;

	while(!ficheiro.eof()){
		string line = "", nome="", custo_aloj="";;
		getline(ficheiro,line);
		if(line=="")
			continue;
		istringstream ss;
		ss.str(line);
		ss >> nome >> custo_aloj;
		cout << nome << " " <<custo_aloj<<endl;
		double custo_alojamento = atof(custo_aloj.c_str());


		Destino d1(nome, custo_alojamento);
		destinos.push_back(d1);

		myGraph.addVertex(d1);

	}
	ficheiro.close();
	ficheiro.open("ligacoesDestinos.txt");
	if(!ficheiro){
		cout << "Error opening 'ligacoesDestinos' file!"<<endl;
		return -1;
	}
	while(!ficheiro.eof()){
		string line = "", nome1="", nome2 ="", custo_viaj = "";
		getline(ficheiro,line);
		if(line=="")
			continue;
		istringstream ss;
		ss.str(line);
		ss >> nome1 >> nome2 >> custo_viaj;
		cout << nome1 << " " << nome2 <<" "<<custo_viaj<<endl;
		double custo_viajem = atof(custo_viaj.c_str());

		Destino d1 = getDestinoByName(destinos,nome1);
		Destino d2 = getDestinoByName(destinos,nome2);

		myGraph.addEdge(d1,d2,custo_viajem);
	}

	ficheiro.close();
}
