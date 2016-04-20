#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "segment.h"
#include "u_rand.h"
#include "spchar.h"

using namespace std;
using namespace spchar;

extern void separate(const string, const char, const char, const char);
extern unsigned int percent;
extern bool initialize;
extern bool print;
extern bool debug;

/**Private**/

bool Segment::import_new_vehicle(){
	if (!is_full()){
		unsigned int destination = nodes - 1;
		if (position + 1 < nodes)
			destination = rand() % (nodes - position - 1) + position + 1;
		q.push_front(new Vehicle(position, destination));
		return true;
	}
	return false;
}

unsigned int Segment::init(){
	/*Initializing*/
	unsigned int v = rand() % (capacity + 1);
	for (unsigned int i = 0; i < v; i++)
	if (!import_new_vehicle())
		v--;
	return v;
}

bool Segment::is_last() const { return (right == NULL); }

bool Segment::is_first() const { return (left == NULL); }

Vehicle * Segment::pop(){
	Vehicle * v = q.front();
	q.pop_front();
	if(::print) cout << "A vehicle exited the segment queue!" << endl;
	return v;
}

unsigned int Segment::exit(){
	unsigned int exit = 0;
	if (!is_empty()){
		Vehicle * v = NULL;
		for (unsigned int i = 0; i < q.size(); i++){
			v = q.at(i);
			if (v->is_ready() && v->can_exit()){
				if (::print) v->print();
				delete v;
				q.erase(q.begin() + i);
				exit++;
			}
		}
	}
	return exit;
}

unsigned int Segment::pass(){
	unsigned int pass = 0;
	if (!is_empty()){
		Vehicle * v = NULL;
		for (unsigned int i = 0; i < q.size(); i++){
			v = q.at(i);
			if (v->is_ready() && !v->can_exit()){
				if (right->enter(v)){
					q.erase(q.begin() + i);
					if (::print) v->print();
					pass++;
				}
				else
					break;
			}
		}
	}
	return pass;
}

unsigned int Segment::get_no_of_ready() const{
	unsigned int ready = 0;
	for (unsigned int i = 0; i < q.size(); i++){
		if (q.at(i)->is_ready())
			ready++;
	}
	return ready;
}

/**Public**/

Segment::Segment(const unsigned int position, const unsigned int nodes, const unsigned int capacity, unsigned int& enter_v)
: position(position), nodes(nodes), capacity(capacity), right(NULL), left(NULL), exit_vehicles(true), incoming_vehicles(true)
{
	if (initialize)
		enter_v += init();
	if (::debug){
		cout 
			<< dark_magenta << "\nSegment at position: " << position + 1 << " and max vehicles size: "
			<< capacity << " has just been created!" << rst << endl;
	}
}

void Segment::set_right(Segment* right_seg){
	if (right_seg != NULL)
		right = right_seg;
}

void Segment::set_left(Segment* left_seg){
	if (this != NULL) // last node's segment is NULL , so we can't set_left
		left = left_seg;
}

bool Segment::is_full() const { return  q.size() >= capacity; }

bool Segment::is_empty() const { return  q.size() == 0; }

bool Segment::enter(Vehicle* v){
	if (!is_full()){
		v->set_position(position);
		v->set_not_ready();
		q.push_front(v);
		return true;
	}
	else{
		if (::print) cout << orange << "\nCannot enter, segment " << position + 1 << " is full!" << rst << endl;
		return false;
	}
}

unsigned int Segment::get_capacity() const { return capacity; };

unsigned int Segment::get_load() const { return (capacity > 0 ? (q.size() * 100 / capacity) : 0); }

unsigned int Segment::get_vehicles() const { return q.size(); }

unsigned int Segment::set_ready(){
	unsigned int ready = 0;
	if (!is_empty()){
		unsigned int percent;
		unsigned int size = q.size();
		Vehicle * v = NULL;
		double p = size * ::percent / 100;
		percent = (unsigned int)ceil(p);
		Unique_Rand r(0, --size);

		for (unsigned int i = 0; i < percent; i++){
			v = q.at(r.get());
			v->set_ready();
			ready++;
		}
		if (::debug) r.print();
	}
	return ready;
}

void Segment::set_exit_vehicles(){ exit_vehicles = true; }

void Segment::set_not_exit_vehicles(){ exit_vehicles = false; }

void Segment::set_incoming_vehicles(){ incoming_vehicles = true; }

void Segment::set_not_incoming_vehicles(){ incoming_vehicles = false; }

bool Segment::operate(unsigned int& left_v){
	bool delay = false;

	if (exit_vehicles){
		unsigned int exits = 0;
		if (::print) cout << dark_aqua << "\n-Left the highway: " << rst;
		left_v += exits = exit();
		if (::print) cout << '\n' << dark_aqua << exits << " vehicles left!" << rst;
	}

	if (incoming_vehicles){
		if (!is_first()){
			unsigned int passes = 0;
			if (::print) cout << dark_aqua << "\n-Pass from previous: " << rst;
			passes = left->pass();
			if (::print) cout << '\n' << dark_aqua << passes << " vehicles pass!" << rst;
			delay = passes < left->get_no_of_ready();
		}
	}

	return delay;
}

void Segment::print() const {
	unsigned int load = get_load();
	cout << dark_magenta << underline << "\n\nSegment (Vehicles: " << q.size() << "/" << capacity << " "
		<< get_load_color(load) << load << "%" << rst << dark_magenta << underline << " traffic!):" << rst << ' ';
	for (unsigned int i = 0; i < q.size(); i++)
		q.at(i)->print();
}

Segment::~Segment(){
	if (::debug) cout << dark_magenta << "\nSegment at " << position + 1 << " is about to be destroyed!" << rst << endl;
	while (q.size() > 0){
		delete q.back();
		q.pop_back();
	}
}
