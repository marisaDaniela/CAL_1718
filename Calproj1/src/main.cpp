#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Destino.h"
#include "Graph.h"

using namespace std;

int main(void) {
	ifstream ficheiro;
	string nome;
	string custo_alojS;
	double custo_alojamento;
	Graph<Destino> myGraph;

	ficheiro.open("jurados.txt");

	string line;


	while (getline(ficheiro, line)) {
			istringstream i1;
			string nome, custo_aloj;
			i1.str(line);
			getline(i1, nome, ' ');
			getline(i1, custo_alojS, ';');

			custo_alojamento = stod(custo_alojS);

			Destino d1(nome, custo_alojamento);

			myGraph.addVertex(d1);



		}


}
