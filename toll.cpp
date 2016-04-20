#include <iostream>
#include <string>
#include <cstdlib>		/*Rand*/
#include <sstream>		/*ostringstream*/

#include "toll.h"
#include "spchar.h"

extern bool initialize;
extern bool print;
extern bool debug;

using namespace std;
using namespace spchar;

/**Private**/

void Toll::import_new_vehicle(){
	unsigned int destination = nodes - 1;
	if (position + 1 < nodes)
		destination = rand() % (nodes - position - 1) + position + 1;
	q.push_front(new Vehicle(position, destination));
}

unsigned int Toll::init(){					/*Initializing toll with new vehicles*/
	if (is_active()){
		unsigned int v = rand() % (capacity + 1);
		for (unsigned int i = 0; i < v; i++){
			import_new_vehicle();
			v--;
		}
		return v;
	}
	else
		cout << yellow << "\nThe toll " << toll + 1 << " is currently inactive!" << rst << endl;
	return 0;
}

void Toll::push(Vehicle * v) {
	if (!is_full()){
		q.push_front(v);
		//cout << "The vehicle ";
		if (::print) v->print();
		//cout << "has entered the toll's " << toll + 1 << " queue" << endl;
	}
	else
		cout << "Toll's " << toll + 1 << " queue is full!" << endl;
}

Vehicle * Toll::pop(){
	Vehicle * v = NULL;
	if (!is_empty()){
		v = q.back();
		q.pop_back();
		//cout << "\nThe vehicle ";
		if (::print) v->print();
		//cout << "has exited the toll's " << toll + 1 << " queue!" << (is_epass() ? " (epass)" : "");	
	}
	return v;
}

/**Public**/
Toll::Toll(Segment& s, const bool e, const unsigned int n, const unsigned int p, const unsigned int c, const unsigned int t, unsigned int& enter_v)
: segment(s), epass(e), nodes(n), position(p), capacity(c), toll(t)
{
	if (initialize)
		enter_v = init();

	if (::debug){
		cout << dark_magenta << "\nToll " << toll + 1 << " at position: " << position + 1
			<< " (max vehicles size: " << capacity << (epass ? ", e-pass)" : ")")
			<< " has just been created!" << rst << endl;
	}
}

void Toll::set_capacity(const unsigned int c){ capacity = c; }

bool Toll::is_active() const { return capacity > 0; }

bool Toll::is_full() const { return  q.size() >= capacity; }

bool Toll::is_empty() const { return (q.size() <= 0); }

bool Toll::is_epass() const { return epass; }

unsigned int Toll::get_load() const{
	return (capacity > 0 ? (q.size() * 100 / capacity) : 0);
}

unsigned int Toll::get_vehicles() const { return q.size(); }

unsigned int Toll::get_free_size() const { return capacity - q.size(); }

unsigned int Toll::get_capacity() const { return capacity; }

void Toll::import_vehicle(Vehicle * v){ push(v); }

bool Toll::pass_vehicle_to_segment(){
	if (!segment.is_full()){
		segment.enter(pop());
		return true;
	}
	return false;
}

void Toll::print() const{
	if (is_active()){
		for (unsigned int i = 0; i < q.size(); i++)
			q.at(i)->print();
	}
	else
		cout << yellow<< "Inactive toll!" << rst;
}

Toll::~Toll(){
	while (q.size() > 0){
		delete q.back();
		q.pop_back();
	}

	if (::debug) cout << dark_magenta << "\nToll " << toll + 1 << " is about to be destroyed!" << rst << endl;
}
