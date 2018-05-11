#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector <int> compute_prefix_function(string pattern) {
	int m = pattern.length();
	vector<int> pi(m,0);
	int k = 0;

	for(int i = 2; i <= m; i++) {
		while(k > 0 && pattern[k] != pattern[i-1]) {
			k = pi[k-1];
		}
		if(pattern[k]==pattern[i-1])
			k = k+1;
		pi[i-1] = k;
	}
	return pi;
}

int kmpMatcher(string text, string pattern) {
	int n = text.length();
	int m = pattern.length();

	vector<int> pi = compute_prefix_function(pattern);
	int q = 0;
	for(int i = 1; i <= n; i++) {
		while(q > 0 && pattern[q]!=text[i-1]){
			q = pi[q-1];
		}
		if(pattern[q]==text[i-1])
			q = q + 1;
		if(q == m){
			cout << "Pattern occurs with shift " << i - m << endl;
			q = pi[q-1];
		}
	}

	return 0;
}

int numStringMatching(string filename,string toSearch) {
	// TODO
}


int editDistance(string pattern, string text) {
	// TODO
	return 0;
}

float numApproximateStringMatching(string filename,string toSearch) {
	// TODO
	return 0;
}

