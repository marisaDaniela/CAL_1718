/*
 * Agencia.cpp
 *
 */

#include "Agencia.h"

void Agencia::leFicheiros(){
	leFicheiroAlojamentos("lisboa");
	leFicheiroAlojamentos("berlim");
	leFicheiroAlojamentos("bruxelas");
	leFicheiroAlojamentos("madrid");
	leFicheiroAlojamentos("amesterdao");
	leFicheiroAlojamentos("paris");
	leFicheiroAlojamentos("praga");
	lerPontosDeInteresse();
	pesquisaAproximada("torre");
}

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

		custo = atof(custoS.c_str());

		Alojamento *a = new Alojamento(cidade, custo);
		a->setDatas(criaDatas(dataInicio,dataFim));

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

void Agencia::lerPontosDeInteresse(){
	ifstream is;
	is.open("pontosDeInteresse.txt");
	if(!is) {
		cout << "Error opening file <pontosDeInteresse.txt>!"<<endl;
		exit(1);
	}

	while(!is.eof()){
		string buf="",word ="";
		getline(is,buf);
		if(buf.length()==0)
			continue;

		word = chopString(buf,"-");
		set<string> points;
		while(buf.find(",")!=string::npos){
			string place = chopString(buf,",");
			points.insert(place);
		}
		pontosInteresse[word] = points;

	}

	is.close();
}

/**
 * Cuts the string on the delimiter.
 * @Param buf - The dictionary line
 * @Param delimiter - The delimiter where it should be cut
 * @Return value: the word between the beggining of the string and the specified delimiter.
 */
string Agencia::chopString(string &buf, string delimiter){
	string word = "";
	size_t pos = buf.find(delimiter);
	word = buf.substr(0, pos);
	buf.erase(0, pos+2);
	return word;
}

vector<Alojamento *> Agencia::getCityVector(string nomeCidade) const{
	vector<Alojamento *> a;
	if(nomeCidade == "Amesterdao")
		a = amesterdao;
	else if(nomeCidade == "Berlim")
		a = berlim;
	else if(nomeCidade == "Bruxelas")
		a = bruxelas;
	else if(nomeCidade == "Lisboa")
		a = lisboa;
	else if(nomeCidade == "Madrid")
		a = madrid;
	else if(nomeCidade == "Paris")
		a = paris;
	else if(nomeCidade == "Praga")
		a = praga;
	return a;
}

void Agencia::verAlojamentos(string nomeCidade) {
	vector<Alojamento *> a = getCityVector(nomeCidade);

	for (int i = 0; i < a.size(); i++)
		cout << *(a[i]) << endl;
}


double Agencia::getCustoTempo(string data, int dias, string cidade) {
	Data data1(data);

	double custo = 0;
	int daysleft = 0;
	bool start = false;

	vector<Alojamento *> city = getCityVector(cidade);

	bool done = false;

	for(int i=0; i<city.size();i++){
		for(auto data : city[i]->getDatas()){
			if(data1.getDia()==data->getDia() && data1.getMes()==data->getMes() && data1.getAno()==data->getAno()){
				daysleft = dias;
				start = true;
			}
			if(start){
				daysleft--;
				custo += city[i]->getCusto();
				if(daysleft==0){
					done = true;
					break;
				}
			}
		}
		if(done)
			break;
	}

	return custo;
}

vector<string> Agencia::pesquisaAproximada(string word){
	vector<string> matches;
	vector<string> paises;
	const float threshold = 0.3;

	for (map<string,set<string>>::iterator it=pontosInteresse.begin(); it!=pontosInteresse.end(); ++it){
	    cout << "Getting points in " << it->first << "..."<< endl;
	    for(auto point: it->second){
	    	int num = editDistance(word,point);
	    	size_t max = word.length();
	    	if(point.length()>max)
	    		max = point.length();
	    	float result = (float) num/max;
	    	result = 1 - result;
	    	if(result>=threshold){
	    		matches.push_back(point);
	    		paises.push_back(it->first);
	    	}
	    }
	}

	for(int i=0; i<matches.size(); i++){
		cout << paises[i] << "-" << matches[i]<<endl;
	}
	return matches;
}

int Agencia::editDistance(string pattern, string text)
{
	int n=text.length();
	vector<int> d(n+1);
	int old,neww;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) neww = old;
			else {
				neww = min(old,d[j]);
				neww = min(neww,d[j-1]);
				neww = neww +1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

bool Agencia::pesquisaExata(string name) {

	for (map<string,set<string> >::iterator it= pontosInteresse.begin(); it!= pontosInteresse.end(); ++it) {
		//cout << it->first << " => " ;// << it->second << '\n';
		for(auto point: it->second) {
			if(point == name)
				return true;
			else
				return false;
		}
	}
	return true;
}
