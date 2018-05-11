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

void inicio(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1);
void clientInterface();

void printCities(vector<Destino> destinos){
	cout << "The cities presented in our travel agency are listed below:\n"<<endl;
		for(int i=0;i<destinos.size();i++){
				cout<<" - " <<destinos[i].getName() << "\n";
		}
}

void computeRoute(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1, bool isDirect){
	printCities(destinos);

	Destino d3;
	cout<< "-> Where are you traveling from? Write the name of the city from the provided list."<<endl;
	bool validCity = false;
	while(!validCity){
		string orig;
		cin >> orig;
		Destino tmp = getDestinoByName(destinos,orig);
		if(tmp.getName()==""){
			cout << "That city does not belong to the available list! City? ";
		}
		else{
			validCity = true;
			d3 = tmp;
		}
	}

	int num;

	if(isDirect){
		num = 1;
		cout<< "\n-> Where are you traveling to? Write the name of the city from the provided list and the desired duration. "<<endl;
	}
	else{
		cout<< "-> How many cities would you like to visit? ";
		bool validNumber = false;
		while(!validNumber){
			readInputInt(num,"Number of cities? ");
			if(num<=destinos.size()-1)
				validNumber = true;
			else
				cout << "We only have " << destinos.size()-1 <<" more cities available! Number of cities? ";
		}
		cout<< "\nWrite per line the name of the city from the provided list and the desired duration. "<<endl;
	}

	PreProcess<Destino> *p = new PreProcess<Destino>(myGraph,num,destinos,d3);
	if(!p->checkIfPossible(d3))
		cout << "There is no route that can take you to all those locations from your starting city!"<<endl;
	else{
		Graph<Destino> newGraph = p->getGraph();
		newGraph.setAgencia(a1);
		string date1, date2;
		cout<< "-> Which would be the minimum starting date? (day/month/year) ";
		readInputDate(date1, "Minimum starting date? ");
		cout<< "\n-> Which would be the maximum final date? (day/month/year) ";
		bool validDate = false;
		while(!validDate){
			readInputDate(date2, "Maximum final date? ");
			if(isValidDate(dataFinal(date1,newGraph.getNumNights()),date2))
				validDate = true;
			else
				cout << "The final date must be bigger or equal to "<<dataFinal(date1,newGraph.getNumNights()) << ", due to number of nights you have selected. Maximum final date? ";
		}
		newGraph.dfs(d3,date1,date2);
	}
	cout<<"\nProgram ended!"<<endl;
}

void pause(){
	cin.ignore();
	cin.clear();
}

void start(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1) {
	int op;

	cout << "*" << string(50, '*') << "*" << endl;
	cout << "*" << string(19, ' ') <<   "TRAVEL AGENCY" <<  string(18, ' ') << "*" << endl;
	cout << "*" << string(50, '*') << "*" << endl;
	cout << "* " << " 1. Exact search       " << string(26, ' ') << "*" << endl;
	cout << "* " << " 2. Approximate search " << string(26, ' ') << "*" << endl;
	cout << "* " << " 3. Back               " << string(26, ' ') << "*" << endl;
	cout << "* " << " 4. Exit               " << string(26, ' ') << "*" << endl;

	cout << "*" << string(50, '*') << "*" << endl;
	cout << "Choose[1-4] : \n";

	bool validInput  = false;
	while(!validInput){
		readInputInt(op, "Choose[1-4]: ");
		if (op <1 || op>4 ){
			cout << "Invalid Option! Choose[1-4]:";
			pause();
		}
		else
			validInput = true;
	}
	switch (op){
		case 1:
			//computeRoute(destinos,myGraph,a1,true);
			//TODO: pesquisa exacta
			clientInterface();
			break;
		case 2:
			//computeRoute(destinos,myGraph,a1,false);
			//TODO: pesquisa aproximada
			cout << "TODO";
			break;
		case 3:
			inicio(destinos,myGraph,a1);
			break;
		case 4:
			exit(1);
			break;
	}

}

void clientInterface() {
	vector<string> places;
	string namePlace;
	int number = 0;
	cout << "How many places would you like to visit?" << endl;
	cin >> number;
	cout << "Which places would you like to visit?" << endl;
	while(number != 0) {
		cout << "-> ";
		cin >> namePlace;
		number--;
		places.push_back(namePlace);
	}
	// TODO: pesquisar no ficheiro pelas palavras deste vetor(lista dos sitios que o utilizador deseja visitar) e depois adicionar a cidade onde for encontrada(se existir) ao percurso do cliente
}

void inicio(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1){
	int op;
	cout << "*" << string(50, '*') << "*" << endl;
	cout << "*" << string(19, ' ') <<   "TRAVEL AGENCY" <<  string(18, ' ') << "*" << endl;
	cout << "*" << string(50, ' ') << "*" << endl;
	cout << "*" << "         Concepcao e Analise de Algoritmos        " << "*" << endl;
	cout << "*" << string(21, ' ') << "2017/2018" << string(20, ' ') << "*" << endl;
	cout << "*" << string(50, ' ') << "*" << endl;
	cout << "*" << string(18, ' ') << "Filipe Lemos   " << string(17, ' ') << "*" << endl;
	cout << "*" << string(18, ' ') << "Marisa Oliveira" << string(17, ' ') << "*" << endl;
	cout << "*" << string(50, ' ') << "*" << endl;
	cout << "*" << string(50, '*') << "*" << endl;
	cout << "Press: 1 to start\n       2 to leave\n";

	bool validInput  = false;
	while(!validInput){
		readInputInt(op, "Choose[1-2]: ");
		if (op != 1 && op !=2 ){
			cout << "Invalid Option! Choose[1-2]:";
			pause();
		}
		else
			validInput = true;
	}

	switch (op){
		case 1:
			start(destinos,myGraph,a1);
			break;
		case 2:
			exit(1);
			break;
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
