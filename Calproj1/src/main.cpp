#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "PreProcess.h"
#include "Agencia.h"
#include "auxFunctions.h"

using namespace std;

#define INF std::numeric_limits<double>::max()

void inicio(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1);

void multiplePlaces(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1){
	cout << "The cities presented in our travel agency are listed below:\n"<<endl;
	for(int i=0;i<destinos.size();i++){
		if(i==destinos.size()-1)
			cout<< destinos[i].getName() << endl;
		else
			cout<<" - " <<destinos[i].getName() << "\n";
	}

	string orig, dest;
	cout<< "-> Where are you travelling from? Write the name of the city from the provided list."<<endl;
	cin >> orig;
	Destino d3 = getDestinoByName(destinos,orig);
	if(d3.getName()==""){
		cout << "That city does not belong to the available list..." <<endl;
		return;
	}

	int num = 0;
	cout<< "-> How many cities would you like to visit? ";
	cin >> num;
	cout<< "\nWrite per line the name of the city from the provided list and the desired duration. "<<endl;
	PreProcess<Destino> *p = new PreProcess<Destino>(myGraph,num,destinos,d3);
	if(!p->checkIfPossible(d3))
		cout << "There is no route that can take you to all those locations from your starting city!"<<endl;
	else{
		string date1, date2;
		cout<< "-> Which would be the minimum starting date? (day/month/year) ";
		cin >>date1;
		cout<< "\n-> Which would be the maximum final date? (day/month/year) ";
		cin >>date2;
		cout << endl;
		Graph<Destino> newGraph = p->getGraph();
		newGraph.setAgencia(a1);
		newGraph.dfs(d3,date1,date2);
	}

	cout<<"\nProgram ended!"<<endl;
	exit(0);
};
void directTravel(){
	//TODO:
	cout << "Viagem apenas de origem e destino? Sem considerar o numero de places xb\n";
};

void pause()
{
	cin.get();
}

void start(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1) {
	unsigned int op;

	cout << "*" << string(50, '*') << "*" << endl;
	cout << "*" << string(19, ' ') <<   "TRAVEL AGENCY" <<  string(18, ' ') << "*" << endl;
	cout << "*" << string(50, '*') << "*" << endl;
	cout << "* " << " 1. Direct travel    " << string(28, ' ') << "*" << endl;
	cout << "* " << " 2. Visit Multiple places" << string(24, ' ') << "*" << endl;
	cout << "* " << " 3. Back             " << string(28, ' ') << "*" << endl;
	cout << "* " << " 0. Exit             " << string(28, ' ') << "*" << endl;

	cout << "*" << string(50, '*') << "*" << endl;
	cout << "Choose[0-3] : \n";

	cin >> op;

	if (op > 5) //
	{
		cout << "Invalid Option! ENTER to try again.\n";
		pause();
		start(destinos,myGraph,a1);
	}
	switch (op)
	{
	case 1:
	{
		directTravel();
	}break;
	case 2:
	{
		multiplePlaces(destinos,myGraph,a1);;
	}break;

	case 3:
	{
		inicio(destinos,myGraph,a1);
	}break;

	case 0:
	{
		exit(1);
	}break;
	}

}

void inicio(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1)
{

	unsigned int op;
	cout << "*" << string(50, '*') << "*" << endl;
	cout << "*" << string(19, ' ') <<   "TRAVEL AGENCY" <<  string(18, ' ') << "*" << endl;
	cout << "*" << string(50, ' ') << "*" << endl;
	cout << "*" << "         Concepcao e Analise de Algoritmos        " << "*" << endl;
	cout << "*" << string(21, ' ') << "2017/2018" << string(20, ' ') << "*" << endl;
	cout << "*" << string(50, ' ') << "*" << endl;
	cout << "*" << string(18, ' ') << "Filipe Lemos   " << string(17, ' ') << "*" << endl;
	cout << "*" << string(18, ' ') << "Diogo Ribeiro? " << string(17, ' ') << "*" << endl;
	cout << "*" << string(18, ' ') << "Marisa Oliveira" << string(17, ' ') << "*" << endl;
	cout << "*" << string(50, ' ') << "*" << endl;
	cout << "*" << string(50, '*') << "*" << endl;
	cout << "Press: 1 to start\n       0 to leave\n";
	cin >> op;

	if ( op > 1)
	{
		cout << "Invalid option! ENTER to try again.\n";
		pause();
		inicio(destinos,myGraph,a1);

	}

	switch (op)
	{
	case 1:
	{

		start(destinos,myGraph,a1);
	}break;
	case 0:
	{
		exit(1);
	}break;
	}
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
	Agencia a1;
	a1.leFicheiros();

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

		myGraph.addVertex(d1,0);

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
	inicio(destinos,myGraph,a1);
	return 0;
}
