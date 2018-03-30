#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Destino.h"
#include "Graph.h"
#include "PreProcess.h"
#include "Agencia.h"

using namespace std;

#define INF std::numeric_limits<double>::max()

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

template <class T>
void getSinglePath(Graph<T> &g, vector<T> path) {
	for(unsigned int i = 0; i < path.size(); i++){
		if(i==path.size()-1)
			cout << path[i].getName() << endl;
		else
			cout << path[i].getName() << " -> ";
	}
}

int main(void) {
	ifstream ficheiro;
	Graph<Destino> myGraph;

	//Apenas para teste:
	//Agencia a1;
//
//	a1.leFicheiroAlojamentos("lisboa");
//	a1.leFicheiroAlojamentos("berlim");
//	a1.leFicheiroAlojamentos("bruxelas");
//	a1.leFicheiroAlojamentos("madrid");
//	a1.leFicheiroAlojamentos("amesterdao");
//
//	a1.verAlojamentos("lisboa");
//	a1.verAlojamentos("berlim");
//	a1.verAlojamentos("bruxelas");
//	a1.verAlojamentos("madrid");
//	a1.verAlojamentos("amesterdao");
//
//
//	a1.getCustoTempo("08/05/2018",2,"lisboa");
//	a1.getCustoTempo("11/11/2018",2,"lisboa");
//	a1.getCustoTempo("04/07/2018",1,"amesterdao");
//	a1.getCustoTempo("10/1/2019",7,"madrid");
//	a1.getCustoTempo("12/11/2018",3,"berlim");

//	Alojamento a1;
//	a1.criaDatas("30/01/2018", "21/05/2018");
//  a1.showDatas();

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
		double custo_viajem = atof(custo_viaj.c_str());

		Destino d1 = getDestinoByName(destinos,nome1);
		Destino d2 = getDestinoByName(destinos,nome2);

		myGraph.addEdge(d1,d2,custo_viajem);
	}
	ficheiro.close();

	cout << "The cities presented in our travel agency are listed below:"<<endl;
	for(int i=0;i<destinos.size();i++){
		if(i==destinos.size()-1)
			cout<<destinos[i].getName() << endl;
		else
			cout<<destinos[i].getName() << ", ";
	}

	string orig, dest;
	cout<< "->Where are you travelling from? Write the name of the city from the provided list."<<endl;
	cin >> orig;
	Destino d3 = getDestinoByName(destinos,orig);
	if(d3.getName()==""){
		cout << "That city does not belong to the available list..." <<endl;
		return -1;
	}

	/*cout<< "->Where are you travelling to? Write the name of the city from the provided list."<<endl;
	cin >> dest;
	Destino d4 = getDestinoByName(destinos,dest);
	if(d3.getName()==""){
		cout << "That city does not belong to the available list..." <<endl;
		return -1;
	}
	myGraph.dijkstraShortestPath(d3);

	if(myGraph.getPath(d3, d4).size()==0){
		cout << "Sorry! We have no route starting in " << orig <<" and ending in "<< dest<<endl;
		return -2;
	}

	double tripCost = myGraph.getTripCost(d4);
	cout << "The optimized route regarding cost (" << tripCost <<" �) is: ";
	getSinglePath(myGraph, myGraph.getPath(d3, d4));
	 */
	int num = 0;
	cout<< "->How many cities would you like to visit? ";
	cin >> num;
	cout<< "\nWrite the name of the cities from the provided list. <city1 city2 city3 ... cityN>"<<endl;
	PreProcess<Destino> *p = new PreProcess<Destino>(num,destinos,d3);
	p->dijkstraAllPairs(myGraph);
	if(!p->checkIfPossible(d3))
		cout << "There is no route that can take you to all those locations from your starting city!"<<endl;
	else
		cout << "Currently trying to find the best price for those days. Wait a minute please..."<<endl;

	cout<<"Program ended"<<endl;
	return 0;
}
