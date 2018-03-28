/*
 * Agencia.h
 *
 */

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

#include "Alojamento.h"

using namespace std;

class Agencia {
	vector<Alojamento *> alojamentos;
public:
	void leFicheiroAlojamentos();

	void verAlojamentos();
};

