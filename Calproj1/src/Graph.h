/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cmath>
#include <algorithm>
#include "MutablePriorityQueue.h"

#include "Agencia.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	double custo = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex<T> *dest, double w);

public:
	bool visited;          // auxiliary field
	int duration = 0;
	Vertex(T in);
	Vertex(T in, int d);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getCusto() const;
	Vertex *getPath() const;
	vector<Edge<T> > getAdj() const;
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Vertex<T>::Vertex(T in, int d): info(in), duration(d) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->custo < vertex.custo;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getCusto() const {
	return this->custo;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template <class T>
vector<Edge<T> > Vertex<T>::getAdj() const{
	return adj;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double custo_viagem;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	Vertex<T> * getDest() const;
	double getCusto() const;
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), custo_viagem(w) {}

template <class T>
Vertex<T> * Edge<T>::getDest() const{
	return dest;
}

template <class T>
double Edge<T>::getCusto() const{
	return custo_viagem;
}

/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	vector<T> order;
	double cost = 0;
	double bestCost;
	vector<string> startDate;
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in, int duration);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;
	double getTripCost(const T &in) const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	vector<T> dfs(Destino origin, Agencia a, string dataInicial, int noites);
	void dfsVisit(Vertex<T> *v, vector<T> & res, vector<string> & dates, Vertex<T> *src, Agencia a, string dataInicial );
	vector<T> dfs(Destino origin, Agencia a, string dataInicial, string maxDataFinal);
	bool allVisited() const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

template <class T>
double Graph<T>::getTripCost(const T &in) const{
	double cost = 0;
	Vertex<T> *dest= findVertex(in);
	cost = dest->custo;
	return cost;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in, int duration) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in, duration));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	auto orig = findVertex(origin);
	if(orig == NULL)
		return;
	for (auto v : vertexSet){
		v->custo = INF;
		v->path = NULL;
	}
	orig->custo = 0;
	MutablePriorityQueue<Vertex<T> > q;
	q.insert(orig);
	while(!q.empty()){
		auto v = q.extractMin();
		for (auto i = v->adj.begin();i!=v->adj.end();i++){
			if ((*i).dest->custo > v->custo + (*i).custo_viagem){
				double aux = (*i).dest->custo;
				(*i).dest->custo = v->custo + (*i).custo_viagem;
				(*i).dest->path=v;
				if(aux==INF)
					q.insert((*i).dest);
				else
					q.decreaseKey((*i).dest);
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
	vector<T> noPath;
	vector<T> res;
	auto v1 = findVertex(origin);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return res;

	res.push_back(v2->info);
	auto next = v2->path;
	while(next!=v1){
		if(next==NULL)
			return noPath;
		res.push_back(next->info);
		next = next->path;
	}
	res.push_back(next->info);
	reverse(res.begin(),res.end());
	return res;
}


vector<Data*> criaDatas(string d1, string d2) {
	vector<Data*> datas;
	Data dataInicio = Data(d1);
	Data dataFim = Data(d2);

	int dia = dataInicio.getDia();
	int mes = dataInicio.getMes();
	int num = numDias(mes, dataInicio.getAno());

	bool stop = false;


	while(!stop){
		Data *d1 = new Data(dia, mes, dataInicio.getAno());
		datas.push_back(d1);
		if(stop)
			break;
		if(dia==dataFim.getDia() && mes==dataFim.getMes())
			stop = true;
		if(dia == num) {
			dia = 0;
			if(mes < 12)
				mes++;
			else
				mes = 1;
			num = numDias(mes, dataInicio.getAno());

		}
		dia++;
	}
	return datas;
}


string dataFinal(string dataInicio, int duration){
	Data d = Data(dataInicio);

	int diasMes = numDias(d.getMes(),d.getAno());
	int result = d.getDia()+duration;
	if(result>diasMes){
		result -= diasMes;
		int mes = d.getMes()+1;
		d.setMes(mes);
	}

	d.buildString(result,d.getMes(),d.getAno());

	return d.getDataString();
}

string maxPossibleStartDate(int noites, string maxDataFinal){
	Data d = Data(maxDataFinal);

	int diasMes = numDias(d.getMes()-1,d.getAno());
	int result = d.getDia()-noites;
	if(result<=0){
		result = diasMes + result;
		int mes = d.getMes()-1;
		d.setMes(mes);
	}

	d.buildString(result,d.getMes(),d.getAno());

	return d.getDataString();
}

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */

template <class T>
vector<T> Graph<T>::dfs(Destino origin, Agencia a, string dataInicial, string maxDataFinal){
	bestCost = INF;
	vector<T> res;
	vector<string> dates;
	int noites=0;
	for(auto v : vertexSet){
		v->visited = false;
		noites += v->duration;
	}

	Vertex<T> *src = findVertex(origin);
	src->visited = true;

	string maxStartDate = maxPossibleStartDate(noites,maxDataFinal);

	vector<Data*> datas = criaDatas(dataInicial, maxStartDate);

	for(auto d:datas){
		dataInicial = d->getDataString();
		for(Edge<T> w : src->adj){
			if(!w.getDest()->visited){
				Vertex<T> *dest = w.getDest();
				Destino d = dest->getInfo();
				/*cost += w.getCusto();
				cout << "viagem: " << cost << endl;
				cost += a.getCustoTempo(dataInicial,dest->duration,d.getName());
				cout << "estadia: " << cost << endl;*/
				cost += w.getCusto() + a.getCustoTempo(dataInicial,dest->duration,d.getName());
				res.push_back(d);
				dates.push_back(dataInicial);
				//cout << a.getCustoTempo(dataInicial,dest->duration,d.getName()) << dataInicial << ","<< dest->duration << d.getName() <<  endl;
				//cout << "Add: " << d.getName()<< ", currentCost = "<< cost << endl;
				dfsVisit(w.getDest(),res,dates,src, a, dataFinal(dataInicial, dest->duration));
				(w.getDest())->visited = false;
				cost -= w.getCusto() + a.getCustoTempo(dataInicial,dest->duration,d.getName());
				res.pop_back();
				dates.pop_back();
			}

		}
	}
	if(bestCost==INF){
		cout << "We are sorry to inform that there is no route available for that trip..."<<endl;
		return res;
	}
	cout << "BestCost: " << bestCost<<endl;
	cout << "StartDate: " << startDate[0]<<endl;

	cout << origin.getName() << "->";
	for(auto l:order)
		cout << l.getName()<< "->";
	cout<<endl;
	return res;
}


/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res,vector<string> & dates, Vertex<T> *src, Agencia a, string dataInicial){
	if(cost>bestCost)
		return;
	v->visited = true;
	bool srcHere = false;
	double aux = 0;
	for(auto w : v->adj){
		Vertex<T> *dest = w.getDest();
		Destino d = dest->getInfo();
		if(!w.getDest()->visited){
			/*cost += w.getCusto();
			cout << "viagem: " << cost << endl;
			cost += a.getCustoTempo(dataInicial,dest->duration,d.getName());
			cout << "estadia: " << cost << endl;*/
			cost += w.getCusto() + a.getCustoTempo(dataInicial,dest->duration,d.getName());
			res.push_back(d);
			dates.push_back(dataInicial);
			//cout << "->Add: " << d.getName()<< ", currentCost = "<< cost << endl;
			dfsVisit(w.getDest(),res,dates,src, a, dataFinal(dataInicial, dest->duration));
			(w.getDest())->visited = false;
			cost -= w.getCusto() + a.getCustoTempo(dataInicial,dest->duration,d.getName());
			res.pop_back();
			dates.pop_back();
		}
		else if(w.getDest()==src){
			srcHere = true;
			aux = w.getCusto();
		}
	}
	if(srcHere && allVisited()){
		if(cost+aux<bestCost){
			order = res;
			bestCost = cost+aux;
			startDate = dates;
		}
	}
}

template <class T>
bool Graph<T>::allVisited() const {
	for(auto v : vertexSet){
		if(!v->visited)
			return false;
	}
	return true;
}





#endif /* GRAPH_H_ */
