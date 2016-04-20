#include <iostream>
#include <cstdlib>	/*Rand*/
#include "entry.h"
#include "spchar.h"

extern bool toll_size_input;
extern bool print;
extern bool debug;

using namespace std;
using namespace spchar;

const unsigned int max_tolls = 15;
const unsigned int max_toll_size = 10;

/*Private*/

unsigned int Entry::get_free_size(){ return capacity - get_vehicles(); }

unsigned int Entry::import_in_tolls(){
	/*Import new vehicles at tolls:*/
	unsigned int imports = 0, max_imports = get_free_size();
	if (::print) cout << dark_aqua << "\n-Importing at the tolls: " << rst;
	if (max_imports > 0){
		max_imports = rand() % max_imports;
		for (unsigned int j = 0; j < max_imports; j++){
			if (import_vehicle())
				imports++;
			else{
				if (::print) cout << yellow << "All tolls are full now!" << rst << endl;
				break;
			}
		}
	}
	return imports;
}

bool Entry::import_vehicle(){
	int target;
	if ((target = pick_a_free_toll()) >= 0){
		unsigned int destination = nodes - 1;
		if (position + 1 < nodes)
			destination = rand() % (nodes - position - 1) + position + 1;
		toll[target]->import_vehicle(new Vehicle(-1, destination));
	}
	return target >= 0;
}

int Entry::pick_a_free_toll() const{
	unsigned int a = 0;
	for (unsigned int i = 0; i < tolls; i++){
		if (toll[i]->get_vehicles() <= toll[a]->get_vehicles()){
			if (!toll[i]->is_full()){
				a = i;
			}
		}
	}

	return toll[a]->is_full() ? -1 : a;
}

unsigned int Entry::pass_to_segment(){
	/*Pass vehicles to segment*/
	if (::print) cout << dark_aqua << "\n-Pass from tolls: " << rst;
	bool space = !segment.is_full();
	unsigned int vehicles_out = 0;

	for (unsigned int i = 0; i < K; i++){
		if (!space){
			if (K > 0)
				K = 0; /*K--;*/
			if (::print) cout << yellow << "\nCannot Pass, segment " << position + 1 << " is full!" << rst << endl;
			break;
		}

		/*For all tolls K*/
		if (space){
			for (unsigned int t = 0; t < tolls; t++){
				if (!toll[t]->is_empty()){
					space = toll[t]->pass_vehicle_to_segment();
					vehicles_out++;
				}
			}
		}
		else
			continue;

		/*Only for epass (2K)*/
		if (space){
			for (unsigned int t = 0; t < tolls; t++){
				if (toll[t]->is_epass() && !toll[t]->is_empty()){
					space = toll[t]->pass_vehicle_to_segment();
					vehicles_out++;
				}
			}
		}
		else
			continue;
	}

	if (space)
		K++;
	return vehicles_out;
}

/**Public**/

Entry::Entry(const unsigned int p, const unsigned int n, Segment& s, const unsigned int K, unsigned int& enter_v)
: tolls(rand() % max_tolls + 1), nodes(n), position(p), segment(s), K(K), capacity(0), passes(true), imports(true)
{
	unsigned int toll_capacity = 0;
	bool epass;
	toll = new Toll*[tolls];
	for (unsigned int i = 0; i < tolls; i++){
		epass = (rand() % 2 == 1);

		if (toll_size_input){
			do{
				cout << "Enter a positive number for toll " << i + 1 << " capacity: ";
				cin >> toll_capacity;
			} while (toll_capacity < 0);
		}
		else
			toll_capacity = rand() % (max_toll_size + 1);

		capacity += toll_capacity;

		toll[i] = new Toll(s, epass, nodes, position, toll_capacity, i, enter_v);
	}
	if (::debug)
		cout << dark_magenta << "\nEntry at position: " << position + 1 << " and max vehicles size: " << capacity << " has just been created!" << rst << endl;
}

void Entry::set_passes(){ passes = true; }

void Entry::set_not_passes(){ passes = false; }

void Entry::set_imports(){ imports = true; }

void Entry::set_not_imports(){ imports = false; }

unsigned int Entry::get_load() const{ return (capacity > 0 ? (get_vehicles() * 100 / capacity) : 0); }

unsigned int Entry::get_vehicles() const{
	unsigned int v = 0;
	for (unsigned int i = 0; i < tolls; i++)
		v += toll[i]->get_vehicles();
	return v;
}

unsigned int Entry::get_capacity() const{ return capacity; }

bool Entry::operate(unsigned int& v){
	bool delay = false;

	if (passes){
		unsigned int passed = 0;
		passed = pass_to_segment();
		if (::print) cout << '\n' << dark_aqua << passed <<" vehicles pass!" << rst;

		delay = passed < get_vehicles();
	}
	else
		cout << orange << "'Pass to segment' functionality at this entrance is currently unavailable!" << rst << endl;

	if (imports){
		unsigned int imports = import_in_tolls();
		v += imports;
		if (::print) cout << '\n' << dark_aqua << imports << " vehicles entered!" << rst;
	}
	else
		cout << orange <<"'imports in tolls' functionality at this entrance is currently unavailable!" << rst << endl;

	return delay;
}

void Entry::print() const{
	unsigned int load = get_load();
	cout
		<< "\n\n" << dark_magenta << underline << "Entry (Vehicles: " << get_vehicles() << "/" << capacity << ' '
		<< get_load_color(load) << load << '%' << rst << dark_magenta << underline << " traffic! - K:" << K << "):" << rst << endl;

	for (unsigned int i = 0; i < tolls; i++){
		load = toll[i]->get_load();
		cout
			<< '\n' << dark_aqua << (toll[i]->is_epass() ? "E-" : "C-") << "Toll " << i + 1
			<< " (" << toll[i]->get_vehicles() << "/" << toll[i]->get_capacity()
			<< ' ' << get_load_color(load) << load << '%' << rst << dark_aqua << " traffic!" << "): " << rst;
		toll[i]->print();
	}
}


Entry::~Entry(){
	if (::debug) cout << dark_magenta << "\nEntry at position " << position + 1 << " is about to be destroyed!" << rst << endl;
	if (toll != NULL){
		for (unsigned int i = 0; i < tolls; i++)
			delete toll[i];
		delete[] toll;
	}
}
