#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "PreProcess.h"
#include "Agencia.h"

const int placesPerDay = 2;

using namespace std;

void inicio(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1);
void clientInterface(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1, bool isApprox);

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
	cout << "* " << " 1. Direct Travel      " << string(26, ' ') << "*" << endl;
	cout << "* " << " 2. Visit Multiple Places" << string(24, ' ') << "*" << endl;
	cout << "* " << " 3. Exact search       " << string(26, ' ') << "*" << endl;
	cout << "* " << " 4. Approximate search " << string(26, ' ') << "*" << endl;
	cout << "* " << " 5. Back               " << string(26, ' ') << "*" << endl;
	cout << "* " << " 6. Exit               " << string(26, ' ') << "*" << endl;

	cout << "*" << string(50, '*') << "*" << endl;
	cout << "Choose[1-6] : \n";

	bool validInput  = false;
	while(!validInput){
		readInputInt(op, "Choose[1-6]: ");
		if (op <1 || op>6 ){
			cout << "Invalid Option! Choose[1-6]:";
			pause();
		}
		else
			validInput = true;
	}

	cin.ignore();

	switch (op){
	case 1:
		computeRoute(destinos,myGraph,a1,true);
		break;
	case 2:
		computeRoute(destinos,myGraph,a1,false);
		break;
	case 3:
		clientInterface(destinos,myGraph,a1,false);
		break;
	case 4:
		clientInterface(destinos,myGraph,a1,true);
		break;
	case 5:
		inicio(destinos,myGraph,a1);
		break;
	case 6:
		exit(1);
	}

}

int getIndexArray(vector<string> vec, string place){
	int index = -1;
	stringToUpper(place);
	for(size_t i=0; i<vec.size();i++){
		string aux = vec.at(i);
		stringToUpper(aux);
		if(aux==place){
			index = i;
			break;
		}
	}
	return index;
}


void clientInterface(vector<Destino> destinos,Graph<Destino> myGraph, Agencia a1, bool isApprox) {

	map<string,int> dates;
	set<string> points;
	map<string, set<string> > pointsInCity;
	string orig;
	Destino d3;

	printCities(destinos);

	cout<< "-> Where are you traveling from? Write the name of the city from the provided list."<<endl;
	bool validCity = false;
	while(!validCity){
		orig = "";
		getline(cin,orig);
		Destino tmp = getDestinoByName(destinos,orig);
		if(tmp.getName()==""){
			cout << "That city does not belong to the available list! City? ";
		}
		else{
			dates[orig] = 0;
			validCity = true;
			d3 = tmp;
		}
	}

	bool valid = false;
	cout << endl;
	cout<< "->Which place(s) or monument(s) would you like to visit? (Press ENTER to stop!)" << endl;

	while(!valid) {
		string name = "";
		cout<< "Place/Monument? ";
		getline(cin,name);
		if(name.length()==0){
			if(pointsInCity.size()==0){
				cout << "You must at least provide a valid point of interest! ";
				continue;
			}
			else
				break;
		}
		else{
			vector<string> matches, paises;
			if(isApprox)
				a1.pesquisaAproximada(name,matches,paises);
			else{
				if(!a1.pesquisaExata(name,matches,paises))
					continue;
			}

			string point = "";
			cout << "->Which point of the provided list were you looking for? (Press ENTER to ignore!)";
			getline(cin,point);
			if(point.length()==0)
				continue;
			else{
				int index = getIndexArray(matches,point);
				if(index==-1)
					cout << "That word wasn't on the list." <<endl;
				else{

					if(paises.at(index)==orig){
						cout << "That point of interest belongs to the selected origin. Please pick places that do not belong to your origin city." <<endl;
					}
					else{
						auto retPoints = points.insert(point);
						if(retPoints.second==false){
							cout << "That point was already selected!" <<endl;
							continue;
						}

						auto it = pointsInCity.find(paises.at(index));
						if (it == pointsInCity.end()){
							set<string> tmp;
							tmp.insert(point);
							pointsInCity[paises.at(index)] = tmp;
							dates[paises.at(index)]=1;
						}
						else{
							set<string> tmp = pointsInCity.at(paises.at(index));
							tmp.insert(point);
							pointsInCity[paises.at(index)] = tmp;
							dates.at(paises.at(index))++;
						}

						cout << "Point of interest added!" <<endl;
					}
				}
			}
		}
	}

	for(auto it=dates.begin(); it!=dates.end(); ++it){
		int aux = ceil((float)it->second/placesPerDay);
		(it->second) = aux;
	}

	PreProcess<Destino> *p = new PreProcess<Destino>(myGraph,destinos,d3,dates);
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

	cout <<endl;
	cout << "Lists of points of interest to see:" <<endl;
	for(auto it=pointsInCity.begin(); it!=pointsInCity.end(); ++it){
		string city = it->first;
		stringToUpper(city);
		cout << " " << city << "(" << dates.at(it->first) << " night(s) booked):"<< endl;
		for(auto p:it->second){
			stringToUpper(p);
			if(p==city){
				if(it->second.size()==1)
					cout << "  - Not specified" << endl;
			}
			else
				cout << "  - " <<p << endl;
		}
	}

	cout<<"\nProgram ended!"<<endl;

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
