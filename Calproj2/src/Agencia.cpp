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

void Agencia::pesquisaAproximada(string word, vector<string> &matches, vector<string> &paises){
	int num;
	size_t max;
	float result;
	float threshold = 0.5;
	bool foundOne = false;

	stringToUpper(word);
	cout << "Words that approximately match that input:" <<endl;

	while(!foundOne){
		for (map<string,set<string> >::iterator it=pontosInteresse.begin(); it!=pontosInteresse.end(); ++it){
			string pais = it->first;
			stringToUpper(pais);
			for(auto point: it->second){
				string place = point;
				stringToUpper(place);

				num = editDistance(word,place);
				max = word.length();
				if(point.length()>max)
					max = point.length();

				result = 1- ((float) num/max);
				if(result>=threshold){
					cout << "  " << pais << " - " << place <<endl;
					matches.push_back(point);
					paises.push_back(it->first);
					foundOne = true;
				}
			}
		}
		if(!foundOne)
			threshold /=1.5;
	}
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


void Agencia::pre_kmp(string pattern, vector<int> &prefix)
{
	int m=pattern.length();
	prefix[0]=-1;
	int k=-1;
	for (int q=1; q<m; q++) {
		while (k>-1 && pattern[k+1]!=pattern[q])
			k = prefix[k];
		if (pattern[k+1]==pattern[q]) k=k+1;
		prefix[q]=k;
	}
}

int Agencia::kmp(string text, string pattern)
{
	int num=0;
	int m=pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n=text.length();

	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			num++;
			q=prefix[q];
		}
	}
	return num;
}


bool Agencia::pesquisaExata(string name, vector<string> &matches, vector<string> &paises) {
	bool exists = false;

	for (map<string,set<string> >::iterator it = pontosInteresse.begin(); it!= pontosInteresse.end(); ++it) {
		string pais = it->first;
		stringToUpper(pais);
		for(auto point: it->second) {
			string place = point;
			stringToUpper(place);
			int num = kmp(point, name);

			if(num != 0)
			{
				cout << "  " << pais << " - " << place <<endl;
				matches.push_back(point);
				paises.push_back(it->first);
				exists = true;
			}
		}
	}

	if(!exists)
		cout << "We are sorry to inform that the specified place/monument does not match any substring of our data. ";

	return exists;
}

