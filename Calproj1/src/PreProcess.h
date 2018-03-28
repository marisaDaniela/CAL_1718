#ifndef PREPROCESS_H_
#define PREPROCESS_H_

#include <vector>
#include <iostream>
#include "Destino.h"
#include "Graph.h"

#define INF std::numeric_limits<double>::max()

using namespace std;

template <class T>
class PreProcess{
	vector<Destino> locais;
	Graph<T> newGraph;
	int num;
public:
	PreProcess (int n, vector<Destino> allDestinos);
	PreProcess (int n, vector<Destino> allDestinos, Destino orig);
	void getDestinations(vector<Destino>) ;
	void dijkstraAllPairs( Graph<T> graph);
	bool checkIfPossible(Destino origin);
};

template <class T>
PreProcess<T>::PreProcess(int n, vector<Destino> allDestinos){
	num = n;
	getDestinations(allDestinos);
}

template <class T>
PreProcess<T>::PreProcess(int n, vector<Destino> allDestinos, Destino orig){
	num = n + 1;
	locais.push_back(orig);
	getDestinations(allDestinos);
}

template <class T>
void PreProcess<T>::getDestinations(vector<Destino> destinos){
	for(int i=0;i<num-1;i++){
			bool added = false;
			while(!added){
				string tmp;
				cin >> tmp;
				/**
				 * E A MESMA FUNCAO DO MAIN MAS NAO SEI COMO USAR EM DOIS FICHEIROS DISTINTOS
				 */
				Destino d;
				d.getName() = "";
				for(auto v:destinos){
					if(v.getName()==tmp){
						d = v;
						break;
					}
				}
				/**
				 * Terminou a tal funcao
				 * */
				if(d.getName()==""){
					cout << "That city does not belong to the available list..." <<endl;
				}
				else {
					added = true;
					locais.push_back(d);
				}
			}
		}
	for(auto l:locais)
		newGraph.addVertex(l);
}

template <class T>
void PreProcess<T>::dijkstraAllPairs(Graph<T> graph){
	for(int i=0;i<num;i++){
		graph.dijkstraShortestPath(locais[i]);
		for(int j=0;j<num;j++){
			double cost=INF;
			if(j==i)
				continue;
			if(graph.getPath(locais[i], locais[j]).size()!=0){
				cost = graph.getTripCost(locais[j]);
				newGraph.addEdge(locais[i],locais[j],cost);
			}
		}
	}
	//Imprime ligações
	/*for(auto v:newGraph.getVertexSet()){
		cout<<v->getInfo().getName()<<" ligado a: "<<endl;
		for (auto e:v->getAdj())
			cout<<e.getDest()->getInfo().getName() << endl;
	}*/
}

template <class T>
bool PreProcess<T>::checkIfPossible(Destino origin){
	bool hasRoute[num];
	for(auto v : newGraph.getVertexSet())
		v->visited = false;
	Vertex<T> *src = newGraph.findVertex(origin);
	queue<Vertex<T>* > q;
	q.push(src);
	src->visited = true;

	while(!q.empty()){
		Vertex<T> *v = q.front();
		q.pop();
		for(auto w : v->getAdj()){
			if(!w.getDest()->visited){
				q.push(w.getDest());
				w.getDest()->visited = true;
			}
		}
	}

	for(auto v : newGraph.getVertexSet()){
		if(v->visited == false)
			return false;
	}
	return true;
}

#endif
