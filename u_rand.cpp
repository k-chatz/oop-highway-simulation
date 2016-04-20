#include <iostream>
#include <ctime>
#include <cstdlib>

#include "u_rand.h"

extern bool debug;

#include "spchar.h"

using namespace std;
using namespace spchar;

void inline Unique_Rand::swap_(int& r1, int& r2){ int t = r1; r1 = r2; r2 = t; }

void Unique_Rand::reset(){
	int x = (max - min + 1);
	for (int i = 0; i < x; i++){
		*values[i] = min + i;
	}
}

Unique_Rand::Unique_Rand(const unsigned int min, const unsigned int max)
: min(min), max(max)
{
	if (max >= min){
		index = max - min + 1;
		values = new int*[index];
		for (int i = 0; i < index; i++)
			values[i] = new int(min + i);
		if (::debug)
			cout << dark_magenta << "\nI construct a Unique_Rand object with min value: " << min << " and max value: " << max << rst << endl;
	}
	else{
		cerr << bg_red << black << "\nError:\nCan't create Unique_Random numbers in function 'Unique_Rand::Constructor' with this arguments!" << rst << endl;
		cin.get();
		exit(1);
	}
}

void Unique_Rand::print() const{
	int x = (max - min + 1);
	for (int i = 0; i < x; i++)
		cout << "Values[" << i << "] = " << *values[i] << endl;
}

const int Unique_Rand::get(){
	int x, number = min;
	if (index > 0){
		x = rand() % index;
		number = *values[x];
		swap_(*values[x], *values[--index]);
	}
	else{
		cerr << bg_red << black << "\nError:\nCan't generate more Unique Random numbers in function 'Unique_Rand::Generate'" << rst << endl;
		cin.get();
		reset();
	}
	return number;
}

Unique_Rand::~Unique_Rand(){
	if (::debug)
		cout << dark_magenta << "\nUnique_Rand object with min value: " << min << " and max value: " << max << " is about to be destroyed!" << rst << endl;

	int x = (max - min + 1);
	for (int i = 0; i < x; i++)
		delete values[i];
	delete[] values;
}
