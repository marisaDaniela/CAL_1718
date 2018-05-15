#ifndef PREPROCESS_H_
#define PREPROCESS_H_

#include <queue>
#include "Destino.h"
#include "Graph.h"

#define INF std::numeric_limits<double>::max()

using namespace std;

template <class T>
class PreProcess{
	Graph<T> newGraph;
	int num;
	vector<Destino> locais;

	void getDestinations(vector<Destino>) ;
	void dijkstraAllPairs(Graph<T> graph);
public:
	PreProcess (Graph<T> old, int n, vector<Destino> allDestinos, Destino orig);
	PreProcess (Graph<T> old, vector<Destino> allDestinos, Destino orig, map<string,int> dates);
	bool checkIfPossible(Destino origin);
	void orderAdj();
	Graph<T> getGraph() const;
	vector<Destino> getLocais() const;
};

template <class T>
PreProcess<T>::PreProcess(Graph<T> old, int n, vector<Destino> allDestinos, Destino orig){
	num = n + 1;
	locais.push_back(orig);
	getDestinations(allDestinos);
	dijkstraAllPairs(old);
}

template <class T>
PreProcess<T>::PreProcess (Graph<T> old, vector<Destino> allDestinos, Destino orig, map<string,int> dates){
	num = dates.size();
	locais.push_back(orig);
	newGraph.addVertex(orig,0);

	for (map<string,int>::iterator it = dates.begin(); it!= dates.end(); ++it) {
		Destino d = getDestinoByName(allDestinos, it->first);
		if(d==orig)
			continue;
		locais.push_back(d);
		newGraph.addVertex(d,it->second);
	}
	dijkstraAllPairs(old);
}

template <class T>
void PreProcess<T>::getDestinations(vector<Destino> destinos){
	vector<int> dates;
	dates.push_back(0);

	for(int i=0;i<num-1;i++){
			bool added = false;
			while(!added){
				string tmp;
				cout<< "City: ";
				cin >> tmp ;

				Destino d = getDestinoByName(destinos, tmp);
				Destino checkIfAlreadyInserted = getDestinoByName(locais, tmp);
				if(d.getName()==""){
					cout << "That city does not belong to the available list! ";
				}
				else if(checkIfAlreadyInserted.getName()!="")
					cout << "That city was already selected. Pick another one! ";
				else {
					int days;
					cout<< "Duration: ";
					readInputInt(days,"Duration? ");
					added = true;
					locais.push_back(d);
					dates.push_back(days);
				}
			}
		}
	for(int i=0;i< locais.size();i++)
		newGraph.addVertex(locais[i],dates[i]);
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
	orderAdj();
}

template <class T>
bool PreProcess<T>::checkIfPossible(Destino origin){
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

template <class T>
Graph<T> PreProcess<T>::getGraph() const{
	return newGraph;
}

template <class T>
vector<Destino> PreProcess<T>::getLocais() const{
	return locais;
}

template <class T>
void PreProcess<T>::orderAdj(){
	for(Vertex<T> * v : newGraph.getVertexSet()){
		vector<Edge<T> > adj = v->getAdj();
		//sort(adj.begin(), adj.end());
	}
}

#endif
